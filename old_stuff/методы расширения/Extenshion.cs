using System;
using System.Collections.Generic;
using System.Text;

namespace Extenshion_methods
{
    public static class Extenshion
    {
        public static bool IsPalindrome(this Int32 num)
        {
            string s = num.ToString();
            for (int i = 0, j = s.Length - 1; i < j; i++, j--)
                if (s[i] != s[j])
                    return false;
            return true;
        }
    }
}
