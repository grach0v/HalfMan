//Include libraries
//{

    #include <iostream>
    #include <fstream>
    #include <windows.h>
    #include <limits>
    #include <conio.h>
    #include <cassert>
    #include <cmath>

//}

//Consts
//{

    const size_t DOUBLESIZE = 512;
    const size_t CODELENGTH = 32;

    enum Direction
    {
        //Left = 0,
        //Right = 1
        CLeft = '0',
        CRight = '1',
        ILeft = 0,
        IRight = 1
    };

//}

//Classes
//{

    class WriteBit
    {
        FILE* file;
        char buffer;
        size_t i;

        WriteBit (const WriteBit&);
        operator = (const WriteBit&);

        public:

        WriteBit (const char* filename): file (fopen (filename, "w")), buffer (0), i (0) {}
       ~WriteBit ()
        {
            while (i++)
            {
                buffer = (char) (buffer*2);

                if (i % 8 == 0)
                {
                    putc (buffer, file);
                    break;
                }
            }

            fclose (file);
        }

        bool operator << (char* code)
        {
            //printf ("<< start i = %d\n", i);

            for (int j = 0; code [j] != 0; j++)
            {
                if (i == 0) buffer = 0;

                buffer = (char) (buffer*2); // buffer *= 2
                buffer = (char) (buffer + code [j % 8] - '0'); // buffer += code [i % 8] - '0'

                if (i == 7)
                {
                    //printf ("buffer = %c\n", buffer);
                    //printf ("buffer = %d\n", buffer);
                    putc (buffer, file);
                    buffer = 0;
                }

                i = i % 8;
                i++;
            }

            //printf ("<< finish i = %d\n", i);
            return true; //may be add true -> did putc, false -> didn't
        }
    };

    class ReadBit
    {
        FILE* file;
        unsigned char buffer;
        size_t i;

        ReadBit (const ReadBit&);
        operator = (const ReadBit&);

        public:

        ReadBit (const char* filename): file (fopen (filename, "r")), buffer (0), i (0) {assert (file);}
       ~ReadBit ()
        {
            fclose (file);
        }

        bool operator << (bool& direction)
        {
            if (i == 0) buffer = (unsigned char) getc (file);
            unsigned char ret_direction = buffer;

            ret_direction = (char)(ret_direction / pow (2, 8 - i - 1)); // i dont know how to fix this warning

            ret_direction = ret_direction % 2;

            i++;
            i = i % 8;

            direction = ret_direction;
            return ret_direction;
        }

        bool nextDirection ()
        {
            if (i == 0) buffer = (unsigned char) getc (file);
            unsigned char ret_direction = buffer;

            ret_direction = (char)(ret_direction / pow (2, (8 - i - 1))); // i dont know how to fix this warning

            ret_direction = ret_direction % 2;

            i++;
            i = i % 8;

            return ret_direction;
        }
    };

//}
