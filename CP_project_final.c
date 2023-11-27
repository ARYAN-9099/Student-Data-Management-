#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char subjects[5][50] = {"Calculus for Engineers", "Computer Programming", "Applied Sciences", "Electrical Engineering", "Electronic Devices and Circuits"};

int i = 0;

struct student_info
{
    char f_name[50];
    char l_name[50];
    int r_no;
    char dob[10];
    char password[50];
    int course_marks[5];
    float cgpa;
    float attendance;
    char hostel[10];
    char fees[10];
    char email[50];
} st[55], tp[50], maxt[50];

// credentials for teacher login are userid: 0 and password: admin123
// credentials for student login are userid: roll number and password: first name + date of birth first 4 digits
// credentials for review checker login are userid: -1000 and password: admin123

int student_userpassword_checker(int roll_num, char password[])
{
    int flag = 0;
    for (int j = 0; j < i; j++)
    {
        if (roll_num == st[j].r_no)
        {
            if (strcmp(st[j].password, password) == 0)
            {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}

int login()
{
    int userid;
    char password[20];
    int count = 3;

    while (count)
    {
        printf("Enter userid: ");
        scanf("%d", &userid);
        printf("Enter password: ");
        scanf("%s", password);

        if (userid == 0 && strcmp(password, "admin123") == 0)
        {
            printf("You are logged in as a teacher. Welcome to the program.\n");
            return -1;
        }
        else if (userid == -1000 && strcmp(password, "admin123") == 0)
        {
            printf("You are logged in as a review checker. Welcome to the program.\n");
            return -1000;
        }
        else if (userid > 0 && student_userpassword_checker(userid, password) == 1)
        {
            printf("You are logged in as a student. Welcome to the program.\n");
            return userid;
        }
        else
        {
            printf("Wrong username or password. You have %d attempts left.\n", count - 1);
            count--;
        }
    }

    printf("You have run out of attempts. The program will exit now.\n");
    exit(0);
}

void calculate_cgpa(int studentIndex)
{
    float sum = 0;
    for (int k = 0; k < 5; k++)
    {
        sum += st[studentIndex].course_marks[k];
    }
    st[studentIndex].cgpa = sum / 50;
}

void save_to_file()
{
    FILE *fp;
    fp = fopen("student_data.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int j = 0; j < i; j++)
    {
        fprintf(fp, "%s %s %d %s %s %d %d %d %d %d %.2f %.2f %s %s %s\n", st[j].f_name, st[j].l_name, st[j].r_no, st[j].dob, st[j].email, st[j].course_marks[0], st[j].course_marks[1], st[j].course_marks[2], st[j].course_marks[3], st[j].course_marks[4], st[j].cgpa, st[j].attendance, st[j].hostel, st[j].fees, st[j].password);
    }
    printf("The data is saved successfully.\n");

    fclose(fp);
}

void load_from_file()
{
    FILE *fp;
    fp = fopen("student_data.txt", "r");

    if (fp == NULL)
    {
        printf("No initial data found.\n");
        return;
    }

    while (fscanf(fp, "%s %s %d %s %s %d %d %d %d %d %f %f %s %s %s", st[i].f_name, st[i].l_name, &st[i].r_no, st[i].dob, st[i].email, &st[i].course_marks[0], &st[i].course_marks[1], &st[i].course_marks[2], &st[i].course_marks[3], &st[i].course_marks[4], &st[i].cgpa, &st[i].attendance, st[i].hostel, st[i].fees, st[i].password) != EOF)
    {
        i++;
    }

    printf("The data is loaded successfully.\n");

    fclose(fp);
}

void add_student()
{
    printf("You can add the Student data now !! \n");
    printf("Enter the first name of the Student: ");
    scanf("%s", st[i].f_name);
    printf("Enter the last name of the Student: ");
    scanf("%s", st[i].l_name);
    printf("Enter the roll number of the Student: ");
    scanf("%d", &st[i].r_no);
    strcpy(st[i].email, "bt23cse");
    char r_no_str[10];

    if (st[i].r_no < 10)
    {
        strcat(st[i].email, "00");
        sprintf(r_no_str, "%d", st[i].r_no);
    }
    else if (st[i].r_no < 100)
    {
        strcat(st[i].email, "0");
        sprintf(r_no_str, "%d", st[i].r_no);
    }
    else
    {
        sprintf(r_no_str, "%d", st[i].r_no);
    }

    strcat(st[i].email, r_no_str); // Concatenate the string representation of r_no to email
    strcat(st[i].email, "@iiitn.ac.in");

    printf("Enter the date of birth of the Student: ");
    scanf("%s", st[i].dob);
    printf("Enter the marks\n");

    for (int j = 0; j < 5; j++)
    {
        printf("Enter the marks of %s: ", subjects[j]);
        scanf("%d", &st[i].course_marks[j]);
    }
    calculate_cgpa(i);

    printf("Enter attendance percentage for student : ");
    scanf("%f", &st[i].attendance);

    printf("Hostel required ? (yes/no) : ");
    scanf("%s", st[i].hostel);

    printf("Fees status (paid/unpaid) : ");
    scanf("%s", st[i].fees);

    int k;
    for (k = 0; k < strlen(st[i].f_name); k++)
    {
        st[i].password[k] = st[i].f_name[k];
    }
    for (int m = 0; m < 4; m++)
    {
        st[i].password[k + m] = st[i].dob[m];
    }
    st[i].password[k + 4] = '\0';

    printf("The password is %s", st[i].password);

    ++i;
}

void find_using_roll()
{
    int roll;
    printf("You can find the Student data by entering a roll number now !! \n");
    printf("Enter the roll number of the Student: ");
    scanf("%d", &roll);

    int flag = 0;
    for (int j = 0; j < i; j++)
    {
        if (roll == st[j].r_no)
        {
            printf("\nThe details of the Student with the given roll number are\n");
            printf("The First name of the student is %s\n", st[j].f_name);
            printf("The Last name of the student is %s\n", st[j].l_name);
            printf("The Roll number of the student is %d\n", st[j].r_no);
            printf("The Date of birth of the student is %s\n", st[j].dob);
            printf("The Email of the student is %s\n", st[j].email);
            printf("The CGPA of the student is %.2f\n", st[j].cgpa);
            printf("Attendance for the student is %.2f %% \n", st[j].attendance);
            printf("Hostel occupied ? : %s \n", st[j].hostel);
            printf("Fees status : %s \n", st[j].fees);
            flag = 1;
            printf("\n");
        }
    }
    if (flag == 0)
    {
        printf("No student with the given roll number exists\n");
    }
}

void find_using_fname()
{
    char name[50];
    printf("You can find the Student data by entering the first name now !! \n");
    printf("Enter the first name of the Student: ");
    scanf("%s", name);

    int flag = 0;
    for (int j = 0; j < i; j++)
    {
        if (!strcmp(st[j].f_name, name))
        {
            printf("\nThe details of the student are displayed below\n");
            printf("The First name of the student is %s\n", st[j].f_name);
            printf("The Last name of the student is %s\n", st[j].l_name);
            printf("The Roll number of the student is %d\n", st[j].r_no);
            printf("The Date of birth of the student is %s\n", st[j].dob);
            printf("The Email of the student is %s\n", st[j].email);
            printf("The CGPA of the student is %.2f\n", st[j].cgpa);
            printf("Attendance for the student is %.2f %% \n", st[j].attendance);
            printf("Hostel occupied ? : %s \n", st[j].hostel);
            printf("Fees status : %s \n", st[j].fees);
            flag = 1;
            printf("\n");
        }
    }
    if (flag == 0)
    {
        printf("No student with the given first name exists\n");
    }
}

void del()
{
    int roll;
    printf("Enter the roll number of the student ");
    printf("that you want to delete: ");
    scanf("%d", &roll);

    for (int j = 0; j <= i; j++)
    {
        if (roll == st[j].r_no)
        {
            for (int k = j; k < 49; k++)
            {
                st[k] = st[k + 1];
            }
            i--;
        }
    }

    printf("The details of the student bearing the given roll number are successfully removed.");
}

void detention()
{
    printf("Student in detention are:\n");
    for (int j = 0; j < 50; j++)
    {
        if (st[j].r_no != 0)
        {
            if (st[j].cgpa < 4.0 || st[j].attendance < 75.0)
            {
                printf("%d.\t%s %s\n", st[j].r_no, st[j].f_name, st[j].l_name);
            }
        }
    }
}

void top3()
{
    printf("TOP PERFORMING STUDENTS ARE:\n");

    for (int p = 0; p < 50; p++)
    {
        tp[p] = st[p];
    }

    for (int j = 0; j < 50; j++)
    {
        for (int k = j + 1; k < 50; k++)
        {
            if (tp[k].cgpa > tp[j].cgpa)
            {
                struct student_info temp = tp[j];
                tp[j] = tp[k];
                tp[k] = temp;
            }
        }
    }

    for (int p = 0; p < 3; p++)
    {
        printf("Roll No.%d.  %s %s\n", tp[p].r_no, tp[p].f_name, tp[p].l_name);
    }
}

void update()
{

    int roll;
label:
    printf("Enter the roll number of the student that you want to update: ");
    scanf("%d", &roll);

    for (int j = 0; j < i; j++)
    {
        if (st[j].r_no == roll)
        {
            printf("Choose an option: \n");
            printf("1. First name of the student\n");
            printf("2. Last name of the student\n");
            printf("3. Roll number of the student\n");
            printf("4. Date of Birth\n");
            printf("5. Email\n");
            printf("6. Marks\n");
            printf("7. Attendance\n");
            printf("8. Hostel Status\n");
            printf("9. Fees Status\n");
            printf("10. Exit\n");

            int z;
            scanf("%d", &z);
            switch (z)
            {
            case 1:
                printf("Enter the first name that you want to update : \n");
                scanf("%s", st[j].f_name);
                break;
            case 2:
                printf("Enter the last name that you want to update : \n");
                scanf("%s", st[j].l_name);
                break;
            case 3:
                printf("Enter the new roll number : \n");
                scanf("%d", &st[j].r_no);
                break;
            case 4:
                printf("Enter the new date of birth : \n");
                scanf("%s", st[j].dob);
                break;
            case 5:
                printf("Enter the new email : \n");
                scanf("%s", st[j].email);
                break;
            case 6:
                printf("Which subjust marks you want to update : \n");
                printf("1. Calculus for Engineers\n");
                printf("2. Computer Programming\n");
                printf("3. Applied Sciences\n");
                printf("4. Electrical Engineering\n");
                printf("5. Electronic Devices and Circuits\n");
                int sub;
                scanf("%d", &sub);
                printf("Enter the new marks : \n");
                scanf("%d", &st[j].course_marks[sub - 1]);
                calculate_cgpa(j);
                break;
            case 7:
                printf("Enter the new attendance percentage : \n");
                scanf("%f", &st[j].attendance);
                break;
            case 8:
                printf("Enter the new hostel status : \n");
                scanf("%s", st[j].hostel);
                break;
            case 9:
                printf("Enter the new fees status : \n");
                scanf("%s", st[j].fees);
                break;
            case 10:
                save_to_file();
                printf("Exit successful!!\n");
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
                goto label;
                break;
            }

            printf("The Details of the Student are updated successfully.\n");
        }
    }
}

void count()
{
    printf("The total number of Students is: %d\n", i);
    printf("The maximum number of students is 50\n");
    printf("%d more students can be added\n", 50 - i);
}
void faculty_review(int index)
{
    printf("\n\nFACULTY REVIEW: \n");
    printf("Rate your respective subject's faculty from 1-5: \n 1-Extremely dissatisfied \n 2-Dissatisfied \n 3-Neutral \n 4-Satsfied \n 5-Extremely satsfied\n");
    printf("----------------------------------------\n");

    int arr[5];

    printf("Rate the faculty of '%s': \n", subjects[0]);
    scanf("%d", &arr[0]);
    printf("Rate the faculty of '%s': \n", subjects[1]);
    scanf("%d", &arr[1]);
    printf("Rate the faculty of '%s': \n", subjects[2]);
    scanf("%d", &arr[2]);
    printf("Rate the faculty of '%s': \n", subjects[3]);
    scanf("%d", &arr[3]);
    printf("Rate the faculty of '%s': \n", subjects[4]);
    scanf("%d", &arr[4]);
    printf("----------------------------------------\n");

    FILE *file;
    int matrix[5][5];

    file = fopen("faculty_review.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (fscanf(file, "%d", &matrix[i][j]) != 1)
            {
                printf("Error reading the matrix from the file.\n");
                fclose(file);
                return;
            }
        }
    }

    fclose(file);

    for (int i = 0; i < 5; i++)
    {
        switch (arr[i])
        {
        case 1:
            ++matrix[i][0];
            break;
        case 2:
            ++matrix[i][1];
            break;
        case 3:
            ++matrix[i][2];
            break;
        case 4:
            ++matrix[i][3];
            break;
        case 5:
            ++matrix[i][4];
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    file = fopen("faculty_review.txt", "w");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
void teacher_access()
{
    int choice;

    while (1)
    {
        printf("\n\n\n1. Add student details\n");
        printf("2. Find student details by roll number\n");
        printf("3. Find student details by first name\n");
        printf("4. Update student details by roll number\n");
        printf("5. Delete student details by roll number\n");
        printf("6. Find total number of students\n");
        printf("7. View Detention List\n");
        printf("8. Grade Analysis( View Top 3 performing students)\n");
        printf("9. Save to file\n");
        printf("10. See all data\n");
        printf("11. Exit\n");

        printf("Enter the choice number that you want to perform: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_student();
            break;
        case 2:
            find_using_roll();
            break;
        case 3:
            find_using_fname();
            break;
        case 4:
            update();
            break;
        case 5:
            del();
            break;
        case 6:
            count();
            break;
        case 7:
            detention();
            break;
        case 8:
            top3();
            break;
        case 9:
            save_to_file();
            break;
        case 10:
            for (int j = 0; j < i; j++)
            {
                printf("\n----------------------------------------\n");
                printf("The First name of the student is %s\n", st[j].f_name);
                printf("The Last name of the student is %s\n", st[j].l_name);
                printf("The Roll number of the student is %d\n", st[j].r_no);
                printf("The Date of birth of the student is %s\n", st[j].dob);
                printf("The Email of the student is %s\n", st[j].email);
                printf("The CGPA of the student is %.2f\n", st[j].cgpa);
                printf("Attendance for the student is %.2f %% \n", st[j].attendance);
                printf("Hostel occupied ? : %s \n", st[j].hostel);
                printf("Fees status : %s \n", st[j].fees);
                printf("----------------------------------------\n");
            }
            break;
        case 11:
            save_to_file();
            printf("Exit successful!!");
            exit(0);
            break;
        }
    }
}

void review_checkers_access()
{
    FILE *file;
    int matrix[5][5];

    file = fopen("faculty_review.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (fscanf(file, "%d", &matrix[i][j]) != 1)
            {
                printf("Error reading the matrix from the file.\n");
                fclose(file);
                return;
            }
        }
    }
    fclose(file);

    float avg[5];
    for (int i = 0; i < 5; i++)
    {
        int sumofstars = 0;
        int sumofreviews = 0;
        for (int j = 0; j < 5; j++)
        {
            sumofstars += matrix[i][j]*(j+1);
            sumofreviews += matrix[i][j];
        }
        avg[i] = sumofstars / (float)sumofreviews;
    }

    printf("The average rating of the faculty is: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("%s : %f\n", subjects[i], avg[i]);
    }

}
    

void student_access(int roll_num)
{
    int index;
    for (int j = 0; j < i; j++)
    {
        if (roll_num == st[j].r_no)
        {
            index = j;
        }
    }
    printf("Welcome %s %s\n", st[index].f_name, st[index].l_name);

    // make a menu for student access here only give to access based on index
    int choice;
    while (1)
    {

        if (st[index].cgpa < 4.0 || st[index].attendance < 75.0)
        {
            printf("----------------------------------------\n");
            printf("NOTICE -- You are in detention!!\n");
            printf("----------------------------------------\n\n");
        }

        printf("\n\n\n1. View my details\n");
        printf("2. View my attendance\n");
        printf("3. View my marks\n");
        printf("4. Update Faculty Review\n");
        printf("5. Exit\n");
        printf("6. Exit like a pro\n");

        printf("Enter the choice number that you want to perform: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nThe details of the Student are displayed below\n");
            printf("The First name of the student is %s\n", st[index].f_name);
            printf("The Last name of the student is %s\n", st[index].l_name);
            printf("The Roll number of the student is %d\n", st[index].r_no);
            printf("The Date of birth of the student is %s\n", st[index].dob);
            printf("The Email of the student is %s\n", st[index].email);
            printf("The CGPA of the student is %.2f\n", st[index].cgpa);
            printf("Attendance for the student is %.2f %% \n", st[index].attendance);
            printf("Hostel occupied ? : %s \n", st[index].hostel);
            printf("Fees status : %s \n", st[index].fees);
            break;
        case 2:
            printf("Attendance for the student is %.2f %% \n", st[index].attendance);
            break;
        case 3:
            printf("Marks for the student are : \n");
            for (int j = 0; j < 5; j++)
            {
                printf("%s : %d\n", subjects[j], st[index].course_marks[j]);
            }
            break;
        case 4:
            faculty_review(index);
            break;
        case 5:
            save_to_file();
            printf("Exit successful!!");
            exit(0);
            break;
        case 6:
            system("curl parrot.live");
            exit(0);
            break;
        }
    }
}

void print_pattern(){

    printf("   _____ _             _            _     _____                        _   __  __                                                   _      _____           _                 \n");
    printf("  / ____| |           | |          | |   |  __ \\                      | | |  \\/  |                                                 | |    / ____|         | |                \n");
    printf(" | (___ | |_ _   _  __| | ___ _ __ | |_  | |__) |___  ___ ___  _ __ __| | | \\  / | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_  | (___  _   _ ___| |_ ___ _ __ ___  \n");
    printf("  \\___ \\| __| | | |/ _` |/ _ \\ '_ \\| __| |  _  // _ \\/ __/ _ \\| '__/ _` | | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ \n");
    printf("  ____) | |_| |_| | (_| |  __/ | | | |_  | | \\ \\  __/ (_| (_) | | | (_| | | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_   ____) | |_| \\__ \\ ||  __/ | | | | |\n");
    printf(" |_____/ \\__|\\__,_|\\__,_|\\___|_| |_|\\__| |_|  \\_\\___|\\___\\___/|_|  \\__,_| |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__| |_____/ \\__, |___/\\__\\___|_| |_| |_|\n");
    printf("                                                                                                    __/ |                                        __/ |                      \n");
    printf("                                                                                                   |___/                                        |___/                       \n");

  

}

int main()
{
    load_from_file();

    print_pattern();

    printf("\n");

    int access = login();
    if (access == -1)
    {
        teacher_access();
    }
    else if (access == -1000)
    {
        review_checkers_access();
    }
    else
    {
        student_access(access);
    }

    return 0;
}