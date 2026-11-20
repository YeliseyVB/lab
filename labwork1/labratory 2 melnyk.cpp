#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#endif
}

void drawLine() {
    cout << "==================================================" << endl;
}
//cool
void waitAndReturn() {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Press Enter to continue...";
    cin.get();
}

int main() {
    int choice;

    while (true) {
        clearScreen();
        drawLine();
        cout << "               FUNCTION CALCULATOR               " << endl;
        drawLine();
        cout << "  1 - Start program" << endl;
        cout << "  2 - Help" << endl;
        cout << "  0 - Exit" << endl;
        drawLine();
        cout << "Select option: ";

        if (!(cin >> choice)) {
            cout << "\nError! Enter a number." << endl;
            waitAndReturn();
            continue;
        }

        if (choice == 0) {
            clearScreen();
            drawLine();
            cout << "Goodbye!" << endl;
            drawLine();
            break;
        }

        if (choice == 2) {
            clearScreen();
            drawLine();
            cout << "                      HELP                        " << endl;
            drawLine();
            cout << "Enter a, b, h and n." << endl;
            cout << "You can enter data using keyboard or file." << endl;
            cout << "\nFunction:" << endl;
            cout << "  If x < 0: first formula is used " << endl;
            cout << "  If x >= 0: second formula is used " << endl;
            cout << "\nInput limits:" << endl;
            cout << "  a    - start of the range (-10000 to 10000)" << endl;
            cout << "  b    - the end of the range (a <= b <= 10000)" << endl;
            cout << "  h    - step (0 < h <= 10000)" << endl;
            cout << "  n    - integer parameter (2 <= n <= 20)" << endl;
            cout << "Example: -2 2 0.5 3" << endl;
            drawLine();

            waitAndReturn();
            continue;
        }

        if (choice != 1) {
            cout << "\nIncorrect option!" << endl;
            waitAndReturn();
            continue;
        }

        clearScreen();
        drawLine();
        cout << "  1 - Keyboard input" << endl;
        cout << "  2 - File input (input.txt)" << endl;
        drawLine();
        cout << "Choose input: ";

        int source;
        if (!(cin >> source) || (source != 1 && source != 2)) {
            cout << "\nIncorrect input choice!" << endl;
            waitAndReturn();
            continue;
        }

        double a, b, h;
        int n;

        if (source == 1) {
            clearScreen();
            drawLine();
            cout << "               KEYBOARD INPUT                     " << endl;
            drawLine();

            // a validation
            cout << "Enter a (start of the range):   ";
            if (!(cin >> a) || !isfinite(a) || a < -10000 || a > 10000) {
                cout << "\nError! 'a' must be a valid number between -10000 and 10000." << endl;
                waitAndReturn();
                continue;
            }

            // b validation
            cout << "Enter b (the end of the range): ";
            if (!(cin >> b) || !isfinite(b) || b < a || b > 10000) {
                cout << "\nError! 'b' must be a valid number >= a and <= 10000." << '\n' << endl;
                waitAndReturn();
                continue;
            }

            // h validation
            cout << "Enter h (step):                 ";
            if (!(cin >> h) || !isfinite(h) || h <= 0 || h > 10000) {
                cout << "\nError! Step 'h' must be greater than 0 and <= 10000." << '\n' << endl;
                waitAndReturn();
                continue;
            }


            if ((b - a) / h > 10000) {
                cout << "\nError! Step 'h' is too small (more than 10000 iterations)." << '\n' << endl;
                waitAndReturn();
                continue;
            }

            // n validation
            cout << "Enter n (param):                ";
            if (!(cin >> n) || n < 2 || n > 20) {
                cout << "\nError! 'n' must be an integer between 2 and 20." << '\n' << endl;
                waitAndReturn();
                continue;
            }
	


        }


        
       else {
           clearScreen();
           drawLine();
           cout << "               FILE PROCESSING                    " << endl;
           drawLine();
           cout << "[Process]: Reading input.txt..." << endl;

           ifstream file("input.txt");
           if (!file.is_open()) {
               cout << "Result: Cannot open input.txt!" << endl;
               drawLine();
               waitAndReturn();
               continue;
           }

           if (!(file >> a) || !isfinite(a) || a < -10000 || a > 10000) {
               cout << "Result: Invalid value for 'a' in input.txt!" << endl;
               file.close();
               drawLine();
               waitAndReturn();
               continue;
           }

           if (!(file >> b) || !isfinite(b) || b < a || b > 10000) {
               cout << "Result: Invalid value for 'b' in input.txt!" << endl;
               file.close();
               drawLine();
               waitAndReturn();
               continue;
           }

           if (!(file >> h) || !isfinite(h) || h <= 0 || h > 10000 || (b - a) / h > 10000) {
               cout << "Result: Invalid value for step 'h' in input.txt!" << endl;
               file.close();
               drawLine();
               waitAndReturn();
               continue;
           }

           if (!(file >> n) || n < 2 || n > 20) {
               cout << "Result: Invalid value for 'n' in input.txt!" << endl;
               file.close();
               drawLine();
               waitAndReturn();
               continue;
           }

           file.close();
           cout << "Result: Data loaded successfully." << endl;
       }

       ofstream outFile("results.txt");
       if (!outFile.is_open()) {
           cout << "\nCannot create results.txt!" << endl;
           drawLine();
           waitAndReturn();
           continue;
       }
        
        clearScreen();
        drawLine();
        cout << "                 CALCULATING...                   " << endl;
        drawLine();

        double x = a;
        int count = 0;
        bool calculationSuccess = true;

        while (x <= b && count < 10000) {
            double y;


            if ( a == b) {
                cout << "Calculation just for one point only cause its not on range " << endl;
            }


     
            if (x < 0) {
                double p = 1;
                for (int i = 1; i <= n; i++) {
                    p = p * (1.0 / (i - x));
                }
                y = p;
            }
            else {
                double s = 0;
                for (int j = 0; j <= n - 2; j++) {
                    double p = 1;
                    for (int i = 0; i <= n + 1; i++) {
                        p = p * (x + i + (double)(j * j) / (i + 1));
                    }
                    s = s + p;
                }
                y = 4 * x + s;
            }

            if (!isfinite(y)) {
                cout << "Calculation error at x = " << x << "!" << endl;
                calculationSuccess = false;
                break;
            }

            cout << "x = " << x << "\t\ty = " << y << endl;
            outFile << "x = " << x << "   y = " << y << endl;

            double nextX = x + h;
            if (nextX <= x) {
                cout << "Step is too small!" << endl;
                calculationSuccess = false;
                break;
            }

            x = nextX;
            count++;
        }

        outFile.close();
        drawLine();


        if (calculationSuccess) {
            cout << "Status: Success! Saved to results.txt" << endl;
        }
        else {
            cout << "Status: Terminated due to error." << endl;
        }
 
        drawLine();

        cout << "Press Enter to return to main menu...";
        cin.clear();
        cin.ignore(10000, '\n');
        cin.get();
    }

    return 0;
}
