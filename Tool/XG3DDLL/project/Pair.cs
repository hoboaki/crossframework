using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CrossFramework.XG3D
{
    class Pair<F, S>
    {
        public F First  { get { return this.mFirst; } set { this.mFirst = value; } }
        public S Second { get { return this.mSecond; } set { this.mSecond = value; } }
        //============================================================
        public Pair(F aFirst, S aSecond)
        {
            mFirst = aFirst;
            mSecond = aSecond;
        }

        //============================================================
        F mFirst;
        S mSecond;
    }
}
