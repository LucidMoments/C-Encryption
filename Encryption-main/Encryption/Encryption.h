#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>
#include <stack>
#include <algorithm>
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


    }

    bool EqualZero(Long input)
    {
        for (int i = 0; i < 309; i++)
        {
            if (input.Num[i] != 0)
                return false;
        }
        return true;
    }

    Long Add(Long first, Long second)
    {
        if (EqualZero(first))
            return second;

        if (EqualZero(second))
            return first;

        Long Result;
        int val = 0, carry = 0;
        bool BothNegative = false;


        if (first.negative)
        {
            first.negative = false;
            Result = Sub(second, first);
            return Result;
        }
        else if (second.negative)
        {
            second.negative = false;
            Result = Sub(first, second);
            return Result;
        }
        int i = 0;
        for (i; i < 309; i++)
        {
            val = (first.Num[i] + second.Num[i] + carry) % 100;
            carry = (first.Num[i] + second.Num[i] + carry) / 100;
            Result.Num[i] = val;
        }

        if (carry != 0)
            Result.Num[i] = carry;


        Result.negative = BothNegative;
        return Result;

    }

    Long Sub(Long Original, Long second)
    {

        if (EqualZero(second))
            return Original;

        if (EqualZero(Original))
        {
            second.negative = true;
            return second;
        }


        Long Result, tempResult, first;
        first = Copy(Original);
        int val = 0, NextToMe = 0;
        bool LastNum = false;
        int i = 0;
        for (i; i < 309; i++)
        {
            if (LastNum)
                break;
            if (first.Num[i] >= second.Num[i])
            {
                val = first.Num[i] - second.Num[i];
                Result.Num[i] = val;
            }
            else
            {
                if (i == 309)
                    LastNum = true;

                int temp = i;
                while (temp < 308)
                {
                    temp++;
                    NextToMe++;
                    if (first.Num[temp] != 0)
                    {
                        first.Num[temp] -= 1;
                        first.Num[i] = first.Num[i] + 100;

                        NextToMe--;

                        temp = i + 1;
                        i--;
                        while (NextToMe != 0)
                        {
                            first.Num[temp] = 99;
                            NextToMe--;
                            temp++;;
                        }
                        break;
                    }
                    else if (first.Num[temp] == 0 && temp == 308)
                        LastNum = true;
                }
            }
        }

        if (LastNum == true)
        {
            Result = Sub(second, Original);
            Result.negative = true;
            return Result;
        }

        return Result;

    }

    Long Mul(Long first, Long second)
    {
        Long Result;

        if (EqualZero(first))
            return first;
        if (EqualZero(second))
            return second;


        int val = 0, Help = 0;
        bool negativity = false;
        int i, j;
        for (i = 0; i < 309; i++)
        {
            Long temp;
            for (j = 0; j < 309; j++)
            {
                val = ((first.Num[i] * second.Num[j]) + Help) % 100;
                Help = ((first.Num[i] * second.Num[j]) + Help) / 100;

                temp.Num[j] += val;
            }

            if (i != 0)
            {
                for (int k = 308; k != 0; k--)
                {
                    temp.Num[k] = temp.Num[k - i];
                }
                for (int k = 0; k < i; k++)
                {
                    temp.Num[k] = 0;
                }
            }
            Result = Add(Result, temp);
        }

        Result.negative = negativity;
        return Result;
    }

    Divisibility DivSmall(Long first, Long second)
    {
        Divisibility Result;

        if (EqualZero(first))
        {
            Result.Result = first;
            Result.Remainder = first;
            return Result;
        }

        Long countArray, One, tempResult = first;
        One.Num[0] = 1;

        bool CheckNeg = tempResult.negative;
        do
        {
            tempResult = Sub(tempResult, second);
            CheckNeg = tempResult.negative;
            if (countArray.Num[0] != 99)
                countArray.Num[0] = countArray.Num[0] + 1;
            else
                countArray = Add(countArray, One);
        } while (!CheckNeg);

        if (countArray.Num[0] != 0)
        {
            countArray.Num[0] = countArray.Num[0] - 1;
            Result.Result = countArray;
        }
        else
            Result.Result = Sub(countArray, One);

        Result.Remainder = Add(tempResult, second);

        return Result;
    }

    Divisibility LargeDivision(Long first, Long second)
    {
        Divisibility Result, tempResult;
        Long FirstPart, test;



        bool negativity = false;


        std::reverse(std::begin(first.Num), std::end(first.Num));

        int i = 0;
        while (i != 309)
        {
            do
            {
                FirstPart = PushFront(FirstPart, first.Num[i]);
                test = Sub(FirstPart, second);
                i++;
            } while (test.negative && i != 309);

            tempResult = DivSmall(FirstPart, second);
            Result.Result.Num[309 - i] = tempResult.Result.Num[0];

            FirstPart = tempResult.Remainder;
        }


        Result.Remainder = FirstPart;
        Result.Remainder.negative = negativity;
        Result.Result.negative = negativity;

        return Result;
    }

    Long PwrMod(Long firstOriginal, Long secondOriginal, Long Mod)
    {
        if (EqualZero(firstOriginal))
            return firstOriginal;

        if (EqualZero(secondOriginal))
        {
            Long hop;
            hop.Num[0] = 1;
            return hop;
        }
        std::stack<Crypto::Container> memory;
        Crypto::Container Array;
        Crypto::Divisibility DivisionResult;
        Long first = Copy(firstOriginal);
        Long second = Copy(secondOriginal);
        Long Result, tempResult, Count, tempCount, check, two;
        two.Num[0] = 2;
        tempCount.Num[0] = 1;
        tempResult = first;
        Result = first;

        do
        {
            DivisionResult = LargeDivision(tempResult, Mod);
            Result = DivisionResult.Remainder;
            Count = tempCount;
            Array.Result = Result;
            Array.Count = Count;
            memory.push(Array);


            tempCount = Mul(Count, two);
            tempResult = Mul(Result, Result);

            check = Sub(second, tempCount);
        } while (!check.negative);

        Result = *new Long;
        Result.Num[0] = 1;

        while (!EqualZero(second))
        {
            Array = memory.top();

            if (!Sub(second, Array.Count).negative)
            {
                Result = Mul(Result, Array.Result);
                DivisionResult = LargeDivision(Result, Mod);
                Result = DivisionResult.Remainder;
                second = Sub(second, Array.Count);
            }
            memory.pop();
        }
        return Result;
    }
};


void Decryption(int n, int d, std::vector<int> nums, std::unordered_map<int, char> keyMap)
{
    Crypto Lovely;
    Crypto::Long n_ = Lovely.ArrayString(std::to_string(n));
    Crypto::Long d_ = Lovely.ArrayString(std::to_string(d));

    for (int y : nums)
    {
        Crypto::Long y_ = Lovely.ArrayString(std::to_string(y));
        Crypto::Long ans = Lovely.PwrMod(y_, d_, n_);
        std::string ans_ = Lovely.ToPrint(ans);
        int ansInInt = stoi(ans_);
        std::cout << keyMap[ansInInt];
    }
    std::cout << std::endl;
}
