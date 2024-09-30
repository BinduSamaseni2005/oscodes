#include <stdio.h>

#define MAX 4  // Number of lanes (N-S, E-W, etc.)
#define TIME_SLICE 3  // Each lane gets 3 minutes

// Structure to store vehicle data
struct Lane {
    int id;             // Lane ID
    int vehicles;       // Number of vehicles in the lane
    int remainingVehicles;  // Remaining vehicles to be processed
    int waitingTime;     // Total waiting time for this lane
    int turnaroundTime;  // Total turnaround time for this lane
};

int main() {
    int n = MAX;  // Number of lanes
    struct Lane lanes[MAX] = {
        {1, 15, 15, 0, 0},   // Lane 1 has 15 vehicles
        {2, 12, 12, 0, 0},   // Lane 2 has 12 vehicles
        {3, 18, 18, 0, 0},   // Lane 3 has 18 vehicles
        {4, 10, 10, 0, 0}    // Lane 4 has 10 vehicles
    };

    int totalTime = 0;  // Total time elapsed
    int completed = 0;  // Number of lanes processed
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("Traffic signal simulation:\n");
    
    // Round Robin scheduling to simulate the traffic signal rotation
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (lanes[i].remainingVehicles > 0) {
                printf("\nLane %d is allowed to pass for %d minutes\n", lanes[i].id, TIME_SLICE);

                // Process vehicles from this lane
                if (lanes[i].remainingVehicles > TIME_SLICE) {
                    lanes[i].remainingVehicles -= TIME_SLICE;
                    totalTime += TIME_SLICE;
                } else {
                    // If the remaining vehicles are less than TIME_SLICE, process all and mark as completed
                    totalTime += lanes[i].remainingVehicles;
                    lanes[i].remainingVehicles = 0;
                    completed++;

                    // Calculate turnaround time and waiting time
                    lanes[i].turnaroundTime = totalTime;
                    lanes[i].waitingTime = lanes[i].turnaroundTime - lanes[i].vehicles;

                    // Add to totals for averaging later
                    totalWaitingTime += lanes[i].waitingTime;
                    totalTurnaroundTime += lanes[i].turnaroundTime;
                    
                    printf("Lane %d has finished processing all vehicles.\n", lanes[i].id);
                }
            }
        }
    }

    // Display the results
    printf("\nLane\tVehicles\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", lanes[i].id, lanes[i].vehicles, lanes[i].turnaroundTime, lanes[i].waitingTime);
    }

    // Calculate and display averages
    float avgWaitingTime = totalWaitingTime / n;
    float avgTurnaroundTime = totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2f minutes\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f minutes\n", avgTurnaroundTime);

    return 0;
}
