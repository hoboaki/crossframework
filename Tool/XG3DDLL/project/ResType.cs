using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// リソースの種類。
    /// </summary>
    /// <remarks>C++と同期する必要があります。</remarks>
    enum ResType
    {
        /// <summary>
        /// 何かのデータ。
        /// </summary>
        AnyData,

        /// <summary>
        /// テクスチャ。
        /// </summary>
        Tex,

        /// <summary>
        /// モデル。
        /// </summary>
        Mdl,
    };
}
