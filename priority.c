#include <stdio.h>
#include <limits.h>

struct Customer {
    int id;             // Customer ID
    int billingTime;     // Billing time for each customer
    int arrivalTime;     // Arrival time for each customer
    int priority;        // Priority level (automatically assigned)
    int remainingTime;   // Remaining billing time (for preemption)
    int completionTime;  // Completion time for each customer
    int waitingTime;     // Waiting time for each customer
    int turnaroundTime;  // Turnaround time for each customer
    int isComplete;      // Whether the customer has completed billing
};

int main() {
    int n = 5; // Number of customers

    // Initialize the customers with their billing time, arrival time and automatic priority
    struct Customer customers[5] = {
        {1, 4, 0, 4, 4, 0, 0, 0, 0},    // Priority 4 for C1
        {2, 10, 2, 1, 10, 0, 0, 0, 0},  // Priority 1 for C2
        {3, 2, 4, 2, 2, 0, 0, 0, 0},    // Priority 2 for C3
        {4, 20, 6, 3, 20, 0, 0, 0, 0},  // Priority 3 for C4
        {5, 2, 8, 5, 2, 0, 0, 0, 0}     // Priority 5 for C5
    };

    int currentTime = 0, completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Priority Scheduling with Preemption
    while (completed < n) {
        int highestPriority = INT_MAX;
        int customerToProcess = -1;

        // Find the customer with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (customers[i].arrivalTime <= currentTime && !customers[i].isComplete && customers[i].priority < highestPriority) {
                highestPriority = customers[i].priority;
                customerToProcess = i;
            }
        }

        if (customerToProcess == -1) {
            // If no customer has arrived yet, increase current time
            currentTime++;
            continue;
        }

        // Process the customer with the highest priority
        customers[customerToProcess].remainingTime--;
        currentTime++;

        // If the customer finishes billing
        if (customers[customerToProcess].remainingTime == 0) {
            customers[customerToProcess].isComplete = 1;
            customers[customerToProcess].completionTime = currentTime;
            customers[customerToProcess].turnaroundTime = customers[customerToProcess].completionTime - customers[customerToProcess].arrivalTime;
            customers[customerToProcess].waitingTime = customers[customerToProcess].turnaroundTime - customers[customerToProcess].billingTime;

            // Add to total waiting time and total turnaround time
            totalWaitingTime += customers[customerToProcess].waitingTime;
            totalTurnaroundTime += customers[customerToProcess].turnaroundTime;

            completed++;
        }
    }

    // Display the results
    printf("Customer\tArrival Time\tBilling Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("C%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", customers[i].id, customers[i].arrivalTime, customers[i].billingTime, customers[i].priority, customers[i].completionTime, customers[i].waitingTime, customers[i].turnaroundTime);
    }

    // Calculate and display averages
    float avgWaitingTime = totalWaitingTime / n;
    float avgTurnaroundTime = totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}
