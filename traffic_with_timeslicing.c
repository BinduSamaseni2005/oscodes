#include <stdio.h>

#define TIME_SLICE 3  // Each vehicle gets 3 minutes of travel time

// Structure to store vehicle data
struct Vehicle {
    int id;             // Vehicle ID
    int arrivalTime;    // Arrival time of the vehicle at the junction
    int travelTime;     // Time required by the vehicle to cross the junction
    int remainingTime;  // Remaining time to be processed
    int waitingTime;    // Waiting time for this vehicle
    int turnaroundTime; // Turnaround time for this vehicle
};

int main() {
    int n = 4;  // Number of vehicles
    struct Vehicle vehicles[] = {
        {1, 0, 4, 4, 0, 0},   // Vehicle 1
        {2, 2, 3, 3, 0, 0},   // Vehicle 2
        {3, 3, 2, 2, 0, 0},   // Vehicle 3
        {4, 5, 1, 1, 0, 0}    // Vehicle 4
    };

    int totalTime = 0, completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    int currentTime = 0;  // Current time for processing vehicles

    // Round Robin scheduling to simulate vehicle movement
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (vehicles[i].arrivalTime <= currentTime && vehicles[i].remainingTime > 0) {
                if (vehicles[i].remainingTime > TIME_SLICE) {
                    // Reduce remaining time by the time slice
                    vehicles[i].remainingTime -= TIME_SLICE;
                    currentTime += TIME_SLICE;
                } else {
                    // Vehicle finishes crossing, compute its waiting and turnaround time
                    currentTime += vehicles[i].remainingTime;
                    vehicles[i].remainingTime = 0;
                    completed++;

                    vehicles[i].turnaroundTime = currentTime - vehicles[i].arrivalTime;
                    vehicles[i].waitingTime = vehicles[i].turnaroundTime - vehicles[i].travelTime;

                    // Add to totals for averaging
                    totalWaitingTime += vehicles[i].waitingTime;
                    totalTurnaroundTime += vehicles[i].turnaroundTime;
                }
            }
        }
    }

    // Calculate and display averages
    float avgWaitingTime = totalWaitingTime / n;
    float avgTurnaroundTime = totalTurnaroundTime / n;

    printf("Average Waiting Time: %.2f minutes\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f minutes\n", avgTurnaroundTime);

    return 0;
}
