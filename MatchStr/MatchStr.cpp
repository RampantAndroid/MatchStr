#include <iostream>

using namespace std;

// Assumptions:
// It is assumed needle begins and ends with a wildcard
// Method is case sensitive
// Haystack containing a wildcard is not supported
bool MatchStr(string haystack, string needle)
{    
    int iHaystack = 0;
    int iNeedle = 0;

    // Early exits:
    // Either string is zero length
    // Needle is longer than haystack
    if (haystack.length() == 0 || needle.length() == 0 || 
        haystack.length() < needle.length())
    {
        return false;
    }

    if (needle.length() == 1 && needle[0] == '*')
    {
        return true;
    }

    if (needle[iNeedle] == '*')
        iNeedle++;

    bool singleChar = false;

    while(iHaystack < haystack.length())
    {
        if (haystack[iHaystack] == needle[iNeedle])
        {
            int j = iNeedle;
            int k = 0;
            while (iHaystack + k < haystack.length() && j < needle.length() && haystack[iHaystack + k] == needle[j])
            {
                k++;
                j++;
            }

            if (needle[j] == '*')
            {
                iNeedle = j+1;
                iHaystack += k;
            }
            else if (needle[j] == '?')
            {
                iNeedle = j + 1;
                iHaystack += k;
                singleChar = true;
            }

            if (iNeedle == needle.length())
                return true;
        }
        else if (singleChar == true)
        {
            return false;
        }

        iHaystack++;
    }

    return false;

}

// Open question:
// Haystack = "Hello World"
// Needle = "W*d?"
// Does the '?' at the end, which can match nothing other than the null terminator, get a pass?
// Or does ending the needle with '?' require there to be one final character in the haystack?
// Similarly, what if the needle begins with '?', eg: "?Hello World"
int main()
{
    bool result = MatchStr("Hello world", "*");

    cout << "The result was " << result;
}
