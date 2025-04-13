#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define BUF_SIZE 9

void peculiar_input(void) {
    char inChar1;
    char inChar2;

    printf("Input character 1:\n");
    inChar1 = getchar();

    printf("Input character 2:\n");
    inChar2 = getchar();

    printf("The inChar1 is %c\n", inChar1);
    printf("The inChar2 is %c\n", inChar2);
}

void output_pecular(void) {
    putchar('a');
    sleep(5);
    putchar('b');
    putchar('\n');
    sleep(5);
    putchar('c');
}


void test_with_newline(void) {
    putchar('a');
    putchar('b');
    putchar('\n');
    fflush(stdout);  // 强制刷新缓冲区
    sleep(5);
    putchar('c');
}

void test_without_newline(void) {
    putchar('d');
    putchar('e');
    fflush(stdout);  // 强制刷新缓冲区
    sleep(5);
    putchar('f');
}

void try_scanf_without(void) {
    char name[100];
    int month, day, year;
    double gpa;

    printf("Please enter: lastname birthdate gpa:");
    int i = scanf("%s %d%d%d %lf", name, &month, &day, &year, &gpa);
    putchar('\n');
    printf("Name: %s\nBirthday: %d%d%d\nGPA:%lf", name, month, day, year, gpa);
    printf("The number of successful assigning is:%d\n", i);
    // I enter "Zheng, 2, 22, 2006, 3.0" and receive 
    //      "
    //
    //      Name: ZHeng,
    //      Birthday: 200
    //      GPA:0.000000"
    //
    // The "Zheng 2 22 2006 3.0" input acts as expected, but, 
    //   "Zheng,2,22,2006,3.0" return "Name: Zheng,2,22,2006,3.0
    //  Birthday: -60753622400
    //  GPA:0.000000%  "

    // "Zheng 2/22/2006 3.0" returns 
    //
    //  Name: Zheng
    //  Birthday: 200
    //  GPA:0.000000%                    
}

void try_scanf_() {
    char name[100];
    int month, day, year;
    double gpa;

    printf("Please enter: lastname birthdate gpa:");
    int i = scanf("%s %d/%d/%d %lf", name, &month, &day, &year, &gpa);
    putchar('\n');
    printf("Name: %s\nBirthday: %d,%d,%d\nGPA:%lf", name, month, day, year, gpa);

    // If all is matched, all intext white space will be ignored
    // like the input "
    //
    //
    //
    //      Zheng           2/22        /       2006        3.0"
}

void try_scanf() {
    int a=0, b=0, c=0, d=0;
    scanf("%d/%d", &a, &b);
    scanf("%d %d", &c, &d);
    printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
}

void f(void){
    char buf1[BUF_SIZE];
    char buf2[BUF_SIZE];
    printf("Enter 4 digits (** **): ");
    fgets(buf1, BUF_SIZE, stdin);
    printf("%s\n", buf1);

    //store into buf until SIZE_BUF-1 characters
    //or a newline or the end-of-file
    printf("Enter 4 digits (** **): ");
    fgets(buf2, BUF_SIZE, stdin);
    printf("%s\n", buf2);
}

int filewrite(void) {
    FILE * file = fopen("test_for_writing.png", "r+");
    if(file == NULL) {
        fprintf(stderr, "Cannot open file\n");
        return EXIT_FAILURE;
    }
    fprintf(file, "I ALSO HATE RHET!!!!\n");
    return EXIT_SUCCESS;
}

int main(void) {
    f();
    return EXIT_SUCCESS;
}