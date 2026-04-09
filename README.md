# Debugging Report — All Party Balance: Inconsistent `to_pay`/`to_collect` Meta Totals

## Issue

`to_pay` and `to_collect` values in `meta` are inconsistent across "All", "To Collect", and "To Pay" tabs. "To Collect" tab shows higher `to_collect` than "All" tab — logically impossible.

## Affected Area

**Backend only** — `app/services/report_service.rb`, method `all_party_balance` (lines 1355-1411)

Frontend is working correctly — sends appropriate params, displays API response as-is.

## API Params (Frontend → Backend)

| Tab | Params sent |
|---|---|
| All | `report_type=all_party_balance&end_date=2026-04-09` |
| To Collect | `report_type=all_party_balance&end_date=2026-04-09&is_receivable=true` |
| To Pay | `report_type=all_party_balance&end_date=2026-04-09&is_receivable=false` |

## Evidence — Company 6dd10b0a

| Tab | to_collect | to_pay |
|---|---|---|
| All | 3,815,973.25 | 1,549,943,908.41 |
| To Collect | 3,816,445.60 | 0 |

Difference in `to_collect`: **472.35** = exact `closing_balance` of contact "atest 100", pushed outside threshold in "All" tab by negative-balance contact "adfad".

## Evidence — Company 22ab9001

| Tab | to_collect | to_pay |
|---|---|---|
| All | 179,013.84 | 0 |
| To Collect | 523,266.28 | 0 |

`to_collect` is **3x higher** in "To Collect" than "All" — impossible if totals were correct.

**"All" tab data** — first 11 contacts include 5 zero-balance contacts (AADRITI, AAGAM, AAJ, AAR KAY, AARUSH, Abc) wasting threshold slots.

**"To Collect" tab data** — SQL pre-filters `balance > 0`, so zero-balance contacts removed. Slots filled with paying contacts (ABDULANAGAR 20,006, ABDULLAKHANSHIVAY 50,000, ABDULLAPURKISSAN 134,972.5, ABHI BATTERIES 56,365.92, Abhishek Biotech 82,508.02).

Both tabs return `exceeding_threshold: true` — more than 501 contacts exist.

## Root Cause

**Line 1373:** `LIMIT 501` applied to contacts query **before** the loop (lines 1397-1401) that computes `to_pay`/`to_collect`. Meta totals are partial sums from only 501 contacts, not true totals.

### Code Flow

1. **Line 1356-1358:** `end_date >= Date.today` → `end_date` set to `nil` (today's date gets nullified)
2. **Line 1361-1368:** SQL filter applied based on `is_receivable` (only when `end_date` is blank)
   - "All": no filter → all contacts
   - "To Collect": `WHERE wallets.closing_balance > 0`
3. **Line 1373:** `LIMIT 501` applied
4. **Lines 1376-1401:** `to_pay`/`to_collect` summed from this limited set only

### Why Tabs Differ

- **"All"** → LIMIT 501 gets a mix of positive, zero, negative balance contacts → lower `to_collect`
- **"To Collect"** → SQL pre-filters positives, LIMIT 501 gets only positive contacts → higher `to_collect`

## Secondary Issue

**Line 1356:** `>=` condition nullifies `end_date` when it equals today. Should be `>` (strictly greater) so today's date triggers historical balance calculation via `contact_closing_balance_till_date`.

## Fix Required

**Backend only — `report_service.rb`**

1. **Meta totals:** Compute `to_pay`/`to_collect` via aggregate SQL on **all matching contacts** (no LIMIT). Apply LIMIT 501 only for building the `data` array.
2. **Date check (optional):** Change `>=` to `>` on line 1356 so `end_date = today` is not nullified.
