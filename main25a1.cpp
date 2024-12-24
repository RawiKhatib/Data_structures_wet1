#include "plains25a1.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    int d1, d2;

    // Initialize the Plains object
    Plains *obj = new Plains();

    // Test case 1: Add horses
    obj->add_horse(1, 100);  // Horse 1 with speed 100
    obj->add_horse(2, 200);  // Horse 2 with speed 200
    obj->add_horse(3, 300);  // Horse 3 with speed 300

    // Test case 2: Add herd
    obj->add_herd(1);         // Herd 1

    // Test case 3: Join horses to the herd
    obj->join_herd(1, 1);    // Horse 1 joins Herd 1
    obj->join_herd(2, 1);    // Horse 2 joins Herd 1
    obj->join_herd(3, 1);    // Horse 3 joins Herd 1

    // Test case 4: Horse 1 follows Horse 2
    obj->follow(1, 2);       // Horse 1 follows Horse 2

    // Test case 5: Check if horses in Herd 1 can run together
    obj->can_run_together(1); // Should output "True" if they can run together

    // Test case 6: Horse 2 follows Horse 3
    obj->follow(2, 3);       // Horse 2 follows Horse 3

    // Test case 7: Check if horses in Herd 1 can still run together
    obj->can_run_together(1); // Should still output "True"

    // Test case 8: Horse 3 leaves Herd 1
    obj->leave_herd(3);      // Horse 3 leaves Herd 1

    // Test case 9: Horse 3 re-joins Herd 1
    obj->join_herd(3, 1);    // Horse 3 joins Herd 1 again
    obj->can_run_together(1); // Should output "True"

    // Test case 10: Horse 2 follows Horse 1
    obj->follow(2, 1);       // Horse 2 follows Horse 1

    // Test case 11: Check if horses in Herd 1 can still run together
    obj->can_run_together(1); // Should still output "True"

    // Test case 12: Horse 2 follows Horse 3
    obj->follow(2, 3);       // Horse 2 follows Horse 3

    // Test case 13: Check if horses in Herd 1 can still run together
    obj->can_run_together(1); // Should still output "True"

    // Test case 14: Check if Horse 1 leads Horse 3
    obj->leads(1, 3);         // Should output "True" if Horse 1 leads Horse 3

    // Test case 15: Check if Horse 2 leads Horse 1
    obj->leads(2, 1);         // Should output "False" if Horse 2 does not lead Horse 1

    // Test case 16: Get speeds of all horses
    obj->get_speed(1);        // Get speed of Horse 1
    obj->get_speed(2);        // Get speed of Horse 2
    obj->get_speed(3);        // Get speed of Horse 3

    // Cleanup
    delete obj;

    return 0;
}
