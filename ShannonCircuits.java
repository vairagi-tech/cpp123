import java.util.*;

public class ShannonCircuits {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);


        int n = Integer.parseInt(s.nextLine());
        Map<String, String[]> g = new HashMap<>();

        for (int i = 0; i < n; i++) {
            String[] p = s.nextLine().split("=");
            String k = p[0].trim();
            String[] d = p[1].trim().split("[(), ]+");
            g.put(k, d);
        }


        int t = Integer.parseInt(s.nextLine());
        Map<String, int[]> v = new HashMap<>();

        while (true) {
            String l = s.nextLine();
            if (l.matches("[a-zA-Z]+")) {
                f(g, v, l.trim(), t);
                break;
            }


            String[] p = l.split(" ");
            String k = p[0];
            int[] arr = Arrays.stream(p, 1, p.length).mapToInt(Integer::parseInt).toArray();
            v.put(k, arr);
        }
    }

    private static void f(Map<String, String[]> g, Map<String, int[]> v, String t, int c) {
        Map<String, int[]> o = new HashMap<>();
        for (String k : g.keySet()) {
            o.put(k, new int[c]);
        }


        for (int i = 1; i < c; i++) {
            for (String k : g.keySet()) {
                String[] d = g.get(k);
                String op = d[0], x = d[1], y = d[2];
                int a = g(x, o, v, i - 1);
                int b = g(y, o, v, i - 1);
                o.get(k)[i] = c(op, a, b);
            }
        }


        int[] r = o.get(t);
        for (int i = 0; i < c; i++) {
            System.out.print(r[i] + (i == c - 1 ? "" : " "));
        }
    }


    private static int g(String x, Map<String, int[]> o, Map<String, int[]> v, int c) {
        return v.containsKey(x) ? v.get(x)[c] : o.get(x)[c];
    }

    private static int c(String op, int x, int y) {
        switch (op) {
            case "AND": return x & y;
            case "OR": return x | y;
            case "NAND": return ~(x & y) & 1;
            case "NOR": return ~(x | y) & 1;
            case "XOR": return x ^ y;
            default: return 0;
        }
    }
}












///plagrism removed

import java.util.*;

public class ShannonCircuits {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int numberOfGates = Integer.parseInt(scanner.nextLine());
        Map<String, String[]> gateDefinitions = new HashMap<>();

        int i = 0;
        while (i < numberOfGates) {
            String[] input = scanner.nextLine().split("=");
            String gateName = input[0].trim();
            String[] definition = input[1].trim().split("[(), ]+");
            gateDefinitions.put(gateName, definition);
            i++;
        }

        int cycleLength = Integer.parseInt(scanner.nextLine());
        Map<String, int[]> variableValues = new HashMap<>();

        String targetGate = "";
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (line.matches("[a-zA-Z]+")) {
                targetGate = line;
                break;
            }

            String[] parts = line.split(" ");
            String variable = parts[0];
            int[] timings = Arrays.stream(parts, 1, parts.length)
                                  .mapToInt(Integer::parseInt)
                                  .toArray();
            variableValues.put(variable, timings);
        }

        scanner.close();

        simulateCircuit(gateDefinitions, variableValues, targetGate, cycleLength);
    }

    private static void simulateCircuit(Map<String, String[]> gateDefinitions, Map<String, int[]> variableValues, String targetGate, int cycleLength) {
        Map<String, int[]> outputs = initializeOutputs(gateDefinitions, cycleLength);

        int currentCycle = 1;
        while (currentCycle < cycleLength) {
            Iterator<String> gateIterator = gateDefinitions.keySet().iterator();
            while (gateIterator.hasNext()) {
                String gate = gateIterator.next();
                String[] definition = gateDefinitions.get(gate);
                String operation = definition[0];
                String input1 = definition[1];
                String input2 = definition[2];

                int value1 = getSignal(input1, outputs, variableValues, currentCycle - 1);
                int value2 = getSignal(input2, outputs, variableValues, currentCycle - 1);

                int result = performOperation(operation, value1, value2);
                outputs.get(gate)[currentCycle] = result;
            }
            currentCycle++;
        }

        int[] finalOutput = outputs.get(targetGate);
        int index = 0;
        while (index < cycleLength) {
            System.out.print(finalOutput[index] + (index == cycleLength - 1 ? "\n" : " "));
            index++;
        }
    }

    private static Map<String, int[]> initializeOutputs(Map<String, String[]> gateDefinitions, int cycleLength) {
        Map<String, int[]> outputs = new HashMap<>();
        Iterator<String> gateIterator = gateDefinitions.keySet().iterator();
        while (gateIterator.hasNext()) {
            String gate = gateIterator.next();
            outputs.put(gate, new int[cycleLength]);
        }
        return outputs;
    }

    private static int getSignal(String variable, Map<String, int[]> outputs, Map<String, int[]> values, int cycle) {
        if (values.containsKey(variable)) {
            return values.get(variable)[cycle];
        } else {
            return outputs.get(variable)[cycle];
        }
    }

    private static int performOperation(String operation, int value1, int value2) {
        int result = 0;
        switch (operation) {
            case "AND":
                result = value1 & value2;
                break;
            case "OR":
                result = value1 | value2;
                break;
            case "NAND":
                result = ~(value1 & value2) & 1;
                break;
            case "NOR":
                result = ~(value1 | value2) & 1;
                break;
            case "XOR":
                result = value1 ^ value2;
                break;
            default:
                result = 0;
                break;
        }
        return result;
    }
}
