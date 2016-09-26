using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// バイナライズオプション。
    /// </summary>
    public class BinarizeOption
    {
        /// <summary>
        /// エンディアン。
        /// </summary>
        public XDataConverter.Endian Endian = XDataConverter.Endian.Little;

        /// <summary>
        /// 文字エンコード。
        /// </summary>
        public Encoding Encoding = Encoding.UTF8;

        /// <summary>
        /// バイナリターゲットとなるエンジンの種類。
        /// </summary>
        public Engine TargetEngine = Engine.GL;
    };
}
