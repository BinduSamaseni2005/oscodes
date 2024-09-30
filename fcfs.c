#include <stdio.h>

struct Customer {
    int id;             // Customer ID
    int billingTime;     // Billing time for each customer
    int arrivalTime;     // Arrival time for each customer
    int waitingTime;     // Waiting time for each customer
    int turnaroundTime;  // Turnaround time for each customer
};

int main() {
    int n = 5; // Number of customers
    float totalWaitingTime = 0, totalTurnaroundTime = 0; // To store total times

    // Initialize the customers
    struct Customer customers[5] = {
        {1, 4, 0, 0, 0},
        {2, 10, 2, 0, 0},
        {3, 2, 4, 0, 0},
        {4, 20, 6, 0, 0},
        {5, 2, 8, 0, 0}
    };

    int currentTime = 0;

    // FCFS Scheduling
    for (int i = 0; i < n; i++) {
        // If the current time is less than the arrival time of the next customer, fast forward time
        if (currentTime < customers[i].arrivalTime) {
            currentTime = customers[i].arrivalTime;
        }

        // Waiting time = Current time - Arrival time
        customers[i].waitingTime = currentTime - customers[i].arrivalTime;

        // Completion time = Current time + Billing time
        int completionTime = currentTime + customers[i].billingTime;

        // Turnaround time = Completion time - Arrival time
        customers[i].turnaroundTime = completionTime - customers[i].arrivalTime;

        // Update current time after billing
        currentTime += customers[i].billingTime;

        // Add waiting time and turnaround time to totals
        totalWaitingTime += customers[i].waitingTime;
        totalTurnaroundTime += customers[i].turnaroundTime;
    }

    // Display the results
    printf("Customer\tArrival Time\tBilling Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("C%d\t\t%d\t\t%d\t\t%d\t\t%d\n", customers[i].id, customers[i].arrivalTime, customers[i].billingTime, customers[i].waitingTime, customers[i].turnaroundTime);
    }

    // Calculate and display averages
    float avgWaitingTime = totalWaitingTime / n;
    float avgTurnaroundTime = totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}
