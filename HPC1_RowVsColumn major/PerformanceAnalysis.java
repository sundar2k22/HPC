import java.util.Arrays;
import java.util.Random;

public class PerformanceAnalysis {

    // Task 1: Traverse 2D array in row-major and column-major orders
    public static void traverseArray() {
        int size = 10000; // Array size
        int[][] array = new int[size][size];

        // Initialize the array
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                array[i][j] = i + j;
            }
        }

        // Row-major traversal
        long startTime = System.nanoTime();
        long sumRowMajor = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sumRowMajor += array[i][j];
            }
        }
        long endTime = System.nanoTime();
        System.out.println("Row-major traversal time: " + (endTime - startTime) + " ns");
        long rowtime=  (endTime - startTime);

        // Column-major traversal
        startTime = System.nanoTime();
        long sumColMajor = 0;
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++) {
                sumColMajor += array[i][j];
            }
        }
        endTime = System.nanoTime();
        System.out.println("Column-major traversal time: " + (endTime - startTime) + " ns");
        double betterfactor = (double)(endTime - startTime) / rowtime;
        System.out.println("Row time is " + String.format("%.5f", betterfactor) + " times faster than column time");  }

    // Task 2: Measure execution time of sorting program
    public static void measureSortingEfficiency() {
        int size = 1_000_000; // Array size
        Random random = new Random();
        int[] array = new int[size];

        // Fill array with random integers
        for (int i = 0; i < size; i++) {
            array[i] = random.nextInt();
        }

        // Measure sorting time
        long startTime = System.nanoTime();
        Arrays.sort(array);
        long endTime = System.nanoTime();

        System.out.println("Sorting time: " + (endTime - startTime) + " ns");
    }

    // Task 3: QuickSort implementation
    public static void quickSort(int[] array, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(array, low, high);
            quickSort(array, low, pivotIndex - 1);
            quickSort(array, pivotIndex + 1, high);
        }
    }

    private static int partition(int[] array, int low, int high) {
        int pivot = array[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (array[j] < pivot) {
                i++;
                swap(array, i, j);
            }
        }
        swap(array, i + 1, high);
        return i + 1;
    }

    private static void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public static void profileQuickSort() {
        int size = 1_000_000; // Array size
        Random random = new Random();
        int[] array = new int[size];

        // Fill array with random integers
        for (int i = 0; i < size; i++) {
            array[i] = random.nextInt();
        }

        // Measure QuickSort time
        long startTime = System.nanoTime();
        quickSort(array, 0, array.length - 1);
        long endTime = System.nanoTime();

        System.out.println("QuickSort time: " + (endTime - startTime) + " ns");
    }

    public static void main(String[] args) {
        System.out.println("Task 1: Array Traversal");
        traverseArray();

        System.out.println("\nTask 2: Sorting Efficiency");
        measureSortingEfficiency();

        System.out.println("\nTask 3: Profiling QuickSort");
        profileQuickSort();
    }
}