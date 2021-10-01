#include <iostream>

using namespace std;

bool MatchStr(string haystack, int& iHaystack, string needle, int& iNeedle)
{
    for (int i = iHaystack; i < haystack.length(); i++)
    {
        if (haystack[i] == needle[iNeedle])
        {
            int j = iNeedle;
            int k = 0;
            while (i + k < haystack.length() && j < needle.length() && haystack[i + k] == needle[j])
            {
                k++;
                j++;
            }

            if (needle[j] == '*')
            {
                iHaystack = i + k;
                iNeedle = j + 1;
                return false;
            }

            if (j == needle.length())
                return true;
        }
    }

    return false;
}


// Assumptions:
// It is assumed needle begins and ends with a wildcard
// That the needle string does not begin or end with an explicit wildcard
// A*Z is valid. A* or *Z is invalid.
// Method is case sensitive
// Haystack containing a wildcard is not supported
bool MatchStr(string haystack, string needle)
{    
    int iHaystack = 0;
    int iNeedle = 0;

    // Early exits:
    // Either string is zero length
    // Needle is longer than haystack
    // Needle begins or ends with *
    if (haystack.length() == 0 || needle.length() == 0 || 
        haystack.length() < needle.length() ||
        needle[0] == '*' || needle[needle.length()-1] == '*')
    {
        return false;
    }

    bool retval = MatchStr(haystack, iHaystack, needle, iNeedle);

    // If false and the needle counter is nonzero, then a wildcard was hit.
    // Call a second time with offsets and return result.
    if (retval == false && iNeedle > 0)
    {
        retval = MatchStr(haystack, iHaystack, needle, iNeedle);
    }

    return retval;
}

int main()
{
    bool result = MatchStr("Hello world", "w*ds");

    cout << "The result was " << result;
}
