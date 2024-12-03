import java.util.*;

public class ShannonCircuits {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        // Number of gates
        int n = Integer.parseInt(sc.nextLine());
        Map<String, String[]> gates = new HashMap<>(); // Gate definitions

        // Parse gate definitions
        for (int i = 0; i < n; i++) {
            String[] parts = sc.nextLine().split("=");
            String gateName = parts[0].trim(); // Gate output
            String[] gateDefinition = parts[1].trim().split("[(), ]+");
            gates.put(gateName, gateDefinition);
        }

        // Length of cycles
        int t = Integer.parseInt(sc.nextLine());
        // Parse input variables
        Map<String, int[]> values = new HashMap<>();
        while (true) {
            String line = sc.nextLine();
            if (line.matches("[a-zA-Z]+")) {
                // The last line specifies the target gate
                String targetGate = line.trim();
                simulateCircuit(gates, values, targetGate, t);
                break;
            }
            String[] parts = line.split(" ");
            String inputVar = parts[0];
            int[] timings = Arrays.stream(parts, 1, parts.length)
                    .mapToInt(Integer::parseInt)
                    .toArray();
            values.put(inputVar, timings);
        }
        sc.close();
    }

    private static void simulateCircuit(Map<String, String[]> gates, Map<String, int[]> values, String targetGate, int t) {
        Map<String, int[]> outputs = new HashMap<>();
        // Initialize outputs for all gates.
        for (String gate : gates.keySet()) {
            outputs.put(gate, new int[t]);
        }

        // Simulate each cycle
        for (int cycle = 1; cycle < t; cycle++) {
            for (String gate : gates.keySet()) {
                String[] definition = gates.get(gate);
                String operation = definition[0];
                String input1 = definition[1];
                String input2 = definition[2];

                int value1 = getValue(input1, outputs, values, cycle - 1);
                int value2 = getValue(input2, outputs, values, cycle - 1);

                // Compute the output based on the operation
                int result = computeGate(operation, value1, value2);
                outputs.get(gate)[cycle] = result;
            }
        }

        // Print the output for the target gate
        int[] targetOutput = outputs.get(targetGate);
        for (int i = 0; i < t; i++) {
            System.out.print(targetOutput[i] + (i == t - 1 ? "\n" : " "));
        }
    }

    private static int getValue(String var, Map<String, int[]> outputs, Map<String, int[]> values, int cycle) {
        if (values.containsKey(var)) {
            return values.get(var)[cycle];
        } else {
            return outputs.get(var)[cycle];
        }
    }

    // Updated to use traditional switch statement
    private static int computeGate(String operation, int value1, int value2) {
        int result = 0;
        switch (operation) {
            case "AND":
                result = value1 & value2;
                break;
            case "OR":
                result = value1 | value2;
                break;
            case "NAND":
                result = ~(value1 & value2) & 1; // Keep binary representation
                break;
            case "NOR":
                result = ~(value1 | value2) & 1; // Keep binary representation
                break;
            case "XOR":
                result = value1 ^ value2;
                break;
            default:
                result = 0; // Invalid operation
                break;
        }
        return result;
    }
}





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
        Map<String, int[]> inputValues = new HashMap<>();

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
            inputValues.put(variable, timings);
        }

        scanner.close();
        simulateCircuit(gateDefinitions, inputValues, targetGate, cycleLength);
    }

    private static void simulateCircuit(Map<String, String[]> gates, Map<String, int[]> values, String targetGate, int cycles) {
        Map<String, int[]> outputs = initializeOutputs(gates, cycles);

        int currentCycle = 1;
        while (currentCycle < cycles) {
            for (String gate : gates.keySet()) {
                String[] definition = gates.get(gate);
                String operation = definition[0];
                String input1 = definition[1];
                String input2 = definition[2];

                int value1 = getSignalValue(input1, outputs, values, currentCycle - 1);
                int value2 = getSignalValue(input2, outputs, values, currentCycle - 1);

                int result = performOperation(operation, value1, value2);
                outputs.get(gate)[currentCycle] = result;
            }
            currentCycle++;
        }

        int[] finalOutput = outputs.get(targetGate);
        int index = 0;
        while (index < cycles) {
            System.out.print(finalOutput[index] + (index == cycles - 1 ? "\n" : " "));
            index++;
        }
    }

    private static Map<String, int[]> initializeOutputs(Map<String, String[]> gates, int cycles) {
        Map<String, int[]> outputs = new HashMap<>();
        for (String gate : gates.keySet()) {
            outputs.put(gate, new int[cycles]);
        }
        return outputs;
    }

    private static int getSignalValue(String variable, Map<String, int[]> outputs, Map<String, int[]> values, int cycle) {
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
