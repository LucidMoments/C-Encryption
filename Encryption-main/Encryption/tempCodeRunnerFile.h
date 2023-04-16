class Biggie
{
public:
    struct Long
    {
        int Num[309] = {};
        bool negative = false;
    };

    struct Divisibility
    {
        Long Result;
        Long Remainder;
    };

    struct Container
    {
        Long Result;
        Long Count;
    };
};
class Crypto : public Biggie
{

public:

    Long Copy(Long input)
    {
        Long Result;
        Result.negative = input.negative;
        for (int i = 0; i < 309; i++)
            Result.Num[i] = input.Num[i];
        return Result;
    }
    Long PushFront(Long input, int val)
    {
        Long Result;
        Result.negative = input.negative;
        for (int i = 0; i < 308; i++)
            Result.Num[i + 1] = input.Num[i];

        Result.Num[0] = val;
        return Result;
    }
    Long ArrayString(std::string input)
    {
        reverse(begin(input), end(input));
        int value = 0, iter = 1, outro = 0;
        Long final;
        bool neg = false;
        for (int i = 0; i < input.size(); i++)
        {
            value = value + (input[i] - '0') * iter;
            iter *= 10;
            if (iter == 100)
            {
                final.Num[outro] = value;
                outro++;
                iter = 1;
                value = 0;
            }
        }
        if (value != 0)
            final.Num[outro] = value;
        final.negative = neg;
        return final;
    }
    std::string ToPrint(Long input)
    {
        std::string outro;
        bool Entered = false;
        if (input.negative == true)
            outro += "-";

        std::reverse(std::begin(input.Num), std::end(input.Num));
        int i;
        for (i = 0; i < 309; i++)
        {
            if (input.Num[i] != 0)
                break;
        }
        int iter = 10, value = 0;
        for (int j = 0; j < 2; j++)
        {
            value = input.Num[i] / iter;
            if (value != 0)
            {
                input.Num[i] = input.Num[i] - value * iter;
                outro += (value + '0');
                Entered = true;

            }
            else
            {
                if (Entered)
                {
                    input.Num[i] = input.Num[i] - value * iter;
                    outro += (value + '0');

                }
            }
            iter /= 10;
        }

        i++;
        for (i; i < 309; i++)
        {
            int iter = 10, value = 0;
            for (int j = 0; j < 2; j++)
            {
                value = input.Num[i] / iter;
                input.Num[i] = input.Num[i] - value * iter;
                outro += (value + '0');
                iter /= 10;
            }
        }
        return outro;