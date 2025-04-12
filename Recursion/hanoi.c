#include<stdio.h>
#include<stdlib.h>

void solve_hanoi(int num, int present, int target, int mid) {
    if(num == 1) {
        printf("Move the disk at the top of post %d to the post %d\n", present, target);
        return ;
    }
    solve_hanoi(num-1, present, mid, target);
    printf("Move the disk at the top of post %d to the post %d\n", present, target);
    solve_hanoi(num-1, mid, target, present);
}

int num_hanoi(int n) {
    if(n == 1) {
        return 1;
    }
    return 2 * num_hanoi(n-1) + 1;
} 

int main() {
    printf("We have %d disk at the post %d, we want to move it to post %d, with post %d as imtermedia\n", 6, 0, 2, 1);
    printf("Here is how can we solve it:\n\n");
    solve_hanoi(6, 0, 2, 1);
    printf("\nWe totally use %d steps", num_hanoi(6));
    return EXIT_SUCCESS;
}