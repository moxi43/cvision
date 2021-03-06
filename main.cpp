#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

bool equal_arrays(int array1[3], int array2[3])
{
    int n = 0;
    for (int k = 0; k < 3; k++)
    {
        if ((array1[k] - array2[k]) < 10 && (array1[k] - array2[k]) > -10)
        {
            n += 1;
        }
    }

    if (n == 3)
    {
        return true;
    }
    return false;
}

int nums1[64][64][3];
int nums2[64][64][3];

void preprocessing_arrays(int nnn, const char *first_frame,
                            const char *second_frame)
{

    std::ifstream file1{first_frame};
    std::ifstream file2{second_frame};
    std::vector<int> array1;
    std::vector<int> array2;

    int num = 0;
    int num2 = 0;

    while (file1 >> num)
    {
        array1.emplace_back(num);
    }

    while (file2 >> num2)
    {
        array2.emplace_back(num2);
    }

    int ii = 0;
    for (int i = 0; i < nnn; i++)
    {
        for (int j = 0; j < nnn; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                nums1[i][j][k] = array1[ii]; // we can just multiple indeces here
                ii += 1;
            }
        }
    }

    int iii = 0;
    for (int i = 0; i < nnn; i++)
    {
        for (int j = 0; j < nnn; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                nums2[i][j][k] = array2[iii];
                iii += 1;
            }
        }
    }
}

void recognizing()
{
    int common_cols_left = 0;
    int k = 0;
    int common_cols_right = 0;
    int k_right = 0;

    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (equal_arrays(nums1[j][0], nums2[j][i]))
            {
                k += 1;
            }

            if (equal_arrays(nums1[j][63], nums2[j][63 - i]))
            {
                k_right += 1;
            }
        }
        if (k == 64)
        {
            common_cols_left += 1;
        }
        k = 0;
        if (k_right == 64)
        {
            common_cols_right += 1;
        }
        k_right = 0;
    }

    if (common_cols_left > 0)
    {
        std::cout << "LEFT\n"
                  << common_cols_left;
    }
    else if (common_cols_right > 0)
    {
        std::cout << "RIGHT\n";
    }

    else
    {
        int common_px_left = 0;
        int common_px_right = 0;
        int common_cols_vert = 0;
        int common_cols_down = 0;
        for (int i = 0; i < 64; i++)
        {
            for (int j = 0; j < 64; j++)
            {
                if (equal_arrays(nums1[i][0], nums2[i][j]))
                {
                    common_px_left += 1;
                }
                if (equal_arrays(nums1[63 - i][0], nums2[63 - i][63 - j]))
                {
                    common_px_right += 1;
                }
            }
            if (common_px_left == 64)
            {
                common_cols_vert += 1;
            }
            common_px_left = 0;
            
            if (common_px_right == 64)
            {
                common_cols_down += 1;
            }
            common_px_right = 0;
        }
        if (common_cols_vert > 0)
        {
            std::cout << "UP\n";
        }
        else if (common_cols_down > 0)
        {
            std::cout << "DOWN\n";
        }
    }
}

int main(int argc, char** argv)
{
    preprocessing_arrays(64, argv[1], argv[2]); //taking the first frame and
    recognizing();                              //the second frame
    return 0;
}
