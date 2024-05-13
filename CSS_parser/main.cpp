#include <iostream>
#include "Str.h"
#include "Vec.h"
#include "css.h"
using namespace std;


int main() {
    CSS css;
    String input;
    Vector selectors;
    Vector attributes;
    Vector values;
    char c;
    char temp[2] = { 0 };
    bool czy_sekcja_css = true;
    bool is_selectors = true;
    bool is_attributes = false;
    bool is_values = false;

    while (std::cin) {
        c = (char)getchar();
        temp[0] = c;
        input.append(temp);

        if (input.CommandSection())
            czy_sekcja_css = false;
        else if (input.cssSection())
            czy_sekcja_css = true;

        if (czy_sekcja_css)
        {
            if (c == '{') {
                is_attributes = true;
                is_values = true;
            }
            if(c == ':')
                is_selectors = false;
            if (c == '}') {
                is_selectors = true;
                is_attributes = false;
                is_values = false;
            }
            if (is_selectors)
            {
                if (c == '{' || c == ',')
                {
                    //input.removewhitespaceend();
                    //input.remove_char('\n');
                    if (input != nullptr)
                    {
                        input.remove_char('\n');
                        input.remove_char(' ');
                        input.remove_char('}');
                        input.remove_last_char();
                        selectors.push_back(input);
                        input.clear();
                        cout << "Selectors: " << endl;
                        cout << selectors << endl;
                    }

                }
            }
            
            
            /*String selector = input.Selectors();
            if (selector != nullptr) {
                selector.removeChar(' ');
                selector.removeChar('\n');
                selectors.push_back(selector);
                cout << "Selectors: " << endl;
                cout << selectors << endl;
            }*/


            if (is_attributes)
            {
                if (c == ':')
                {
                    if (input != nullptr)
                    {
                        input.remove_char('\n');
                        input.remove_last_char();
                        attributes.push_back(input);
                        input.clear();
                        cout << "Attributes: " << endl;
                        cout << attributes << endl;
                    } 
                }
            }
            if (is_values)
            {
                if (c == ';')
                {
                    if (input != nullptr) {
                        input.remove_char('\n');
                        input.remove_char(' ');
                        values.push_back(input);
                        input.clear();
                        cout << "Values: " << endl;
                        cout << values << endl;
                    } 
                }

            }

        }
    }
    return 0;
}