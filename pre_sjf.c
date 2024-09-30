#include <stdio.h>
#include <limits.h>

struct Customer {
    int id;             // Customer ID
    int billingTime;     // Billing time for each customer
    int arrivalTime;     // Arrival time for each customer
    int remainingTime;   // Remaining billing time (for preemption)
    int completionTime;  // Completion time for each customer
    int waitingTime;     // Waiting time for each customer
    int turnaroundTime;  // Turnaround time for each customer
    int isComplete;      // Whether the customer has completed billing
};

int main() {
    int n = 5; // Number of customers

    // Initialize the customers
    struct Customer customers[5] = {
        {1, 4, 0, 4, 0, 0, 0, 0},
        {2, 10, 2, 10, 0, 0, 0, 0},
        {3, 2, 4, 2, 0, 0, 0, 0},
        {4, 20, 6, 20, 0, 0, 0, 0},
        {5, 2, 8, 2, 0, 0, 0, 0}
    };

    int currentTime = 0, completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed < n) {
        int minRemainingTime = INT_MAX;
        int shortestCustomer = -1;

        // Find the customer with the shortest remaining billing time that has arrived
        for (int i = 0; i < n; i++) {
            if (customers[i].arrivalTime <= currentTime && !customers[i].isComplete && customers[i].remainingTime < minRemainingTime) {
                minRemainingTime = customers[i].remainingTime;
                shortestCustomer = i;
            }
        }

        if (shortestCustomer == -1) {
            // If no customer has arrived yet, increase current time
            currentTime++;
            continue;
        }

        // Process the shortest job (customer with shortest billing time)
        customers[shortestCustomer].remainingTime--;
        currentTime++;

        // If the customer is done with billing
        if (customers[shortestCustomer].remainingTime == 0) {
            customers[shortestCustomer].isComplete = 1;
            customers[shortestCustomer].completionTime = currentTime;
            customers[shortestCustomer].turnaroundTime = customers[shortestCustomer].completionTime - customers[shortestCustomer].arrivalTime;
            customers[shortestCustomer].waitingTime = customers[shortestCustomer].turnaroundTime - customers[shortestCustomer].billingTime;

            // Add to total waiting time and total turnaround time
            totalWaitingTime += customers[shortestCustomer].waitingTime;
            totalTurnaroundTime += customers[shortestCustomer].turnaroundTime;

            completed++;
        }
    }

    // Display the results
    printf("Customer\tArrival Time\tBilling Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("C%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", customers[i].id, customers[i].arrivalTime, customers[i].billingTime, customers[i].completionTime, customers[i].waitingTime, customers[i].turnaroundTime);
    }

    // Calculate and display averages
    float avgWaitingTime = totalWaitingTime / n;
    float avgTurnaroundTime = totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}
