using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// xmatsetファイル。
    /// </summary>
    public class ResMatSet
    {
        /// <summary>
        /// 名前。
        /// </summary>
        public readonly string Name;


        //============================================================

        //------------------------------------------------------------
        internal void Binarize(XDataConverter.Binarizer aBinarizer)
        {
            var binarizer = aBinarizer;

            // ヘッダ追加
            binarizer.AddStringRef(Name);

            // ...
        }
    }
}
