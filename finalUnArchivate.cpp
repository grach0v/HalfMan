#include "bibrary.hpp"

// Structers
//{

    struct Threesome
    {
        //than will be size_t
        int right_;
        int left_;
        int letter_;

        void print ()
        {
            HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);

            SetConsoleTextAttribute (hConsole, 11);
            std::cout << "right = " << right_ << " ";

            SetConsoleTextAttribute (hConsole, 12);
            std::cout << "left = " << left_ << " ";

            SetConsoleTextAttribute (hConsole, 13);
            std::cout << "letter = " << letter_ << "\n\n";

            SetConsoleTextAttribute (hConsole, 15);
        }

        bool isInteresting ()
        {
            if (right_ == -1 && left_ == -1 && letter_ == -1) return false;
            else                                              return true;
        }

        bool hasLetter () {return letter_ != -1;}

        Threesome(): right_ (-1), left_ (-1), letter_ (-1) {};
    };

//}

//Function Declaration
//{

    void readTablet (const char* fileName, Threesome tree [DOUBLESIZE]);
    void writeToTablet (const std::string& code, int letter, Threesome tree [DOUBLESIZE], size_t* edge);
    void readText (const char* fileName, Threesome tree [DOUBLESIZE], std::string* text);

//}

//Main
//{

    int main (int argc, char* argv [])
    {
        assert (argc == 2);

        Threesome tree [DOUBLESIZE];
        readTablet ("Tree.txt", tree);
        std::string text;
        readText (argv [1], tree, &text);

        getch();
        return 0;
    }

//}

//Function
//{

    void readTablet (const char* fileName, Threesome tree [DOUBLESIZE])
    {
        std::string code;
        int letter;
        size_t edge = 1;
        std::ifstream myfile (fileName);

        if (myfile.is_open())
        {
            while (myfile >> letter >> code)
            {
                writeToTablet (code, letter, tree, &edge);
            }

            myfile.close();
        }
        else std::cout << "Unable to open file\n";
    }

    void writeToTablet (const std::string& code, int letter, Threesome tree [DOUBLESIZE], size_t* edge)
    {
        size_t point = 0;

        for (size_t i = 0; i < code.size(); i++)
        {
            //puts ("start for loop");

            if (code [i] == Direction::CLeft) // make .left .right .direction[]
            {
                if (tree [point].left_ == -1)
                {
                    tree [point].left_ = (*edge);
                    (*edge)++;
                }

                point = tree [point].left_;
            }

            if (code [i] == Direction::CRight)
            {

                if (tree [point].right_ == -1)
                {
                    tree [point].right_ = (*edge);
                    (*edge)++;
                }

                point = tree [point].right_;
            }
        }

        //std::cout << "point = " << point << " letter = " << letter << " code = " << code << '\n';
        tree [point].letter_ = letter;
    }

    void readText (const char* fileName, Threesome tree [DOUBLESIZE], std::string* text)
    {
        ReadBit myfile (fileName);
        size_t point = 0;
        bool direction = 0;

        for (myfile << direction; ; myfile << direction)
        {
            if (direction == Direction::ILeft) point = tree [point].left_;
            else                               point = tree [point].right_;

            //std::cout << "direction = " << direction << '\n';

            if (tree [point].hasLetter())
            {
                text->push_back ((char) tree [point].letter_);

                if (tree [point].letter_ == 0) break;

                point = 0;
            }

            //getch ();
        }

        std::cout << (*text);
    }

//}
