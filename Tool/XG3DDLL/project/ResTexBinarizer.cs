using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// ResTexをバイナリ化するクラス。(GL用)
    /// </summary>
    public class ResTexBinarizer
    {
        /// <summary>
        ///  名前。
        /// </summary>
        public readonly string Name;

        //============================================================

        //------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        /// <param name="aRes"></param>
        public ResTexBinarizer(ResTex aRes)
        {
            Name = aRes.Name;
            mRes = aRes;
        }

        //============================================================

        //------------------------------------------------------------
        /// <summary>
        /// バイナリ化する。
        /// </summary>
        /// <param name="aBinarizer"></param>
        /// <param name="aOption"></param>
        /// <param name="aIndex"></param>
        public void Binarize(
            XDataConverter.Binarizer aBinarizer
            , BinarizeOption aOption
            , int aIndex
            )
        {
            ResTex res = mRes;
            var binarizer = aBinarizer;
            {
                string pixelsLabel = "ResTex[" + res.Name + "].pixels";

                // ヘッダ追加
                binarizer.Add((ushort)aIndex);
                binarizer.Add((ushort)0); // flags
                binarizer.AddStringRef(res.Name);
                binarizer.Add(res.Width);
                binarizer.Add(res.Height);
                binarizer.Add((byte)res.Format);
                binarizer.Add((byte)0);
                binarizer.Add((byte)0);
                binarizer.Add((byte)0);
                binarizer.AddReference(pixelsLabel);

                // その他データ
                binarizer.AddLabel(pixelsLabel);
                for (ushort y = 0; y < res.Height; ++y)
                {
                    for (ushort x = 0; x < res.Width; ++x)
                    {
                        Color pix = res.Pixel(x, y);
                        switch (res.Format)
                        {
                        case ResTex.FormatType.RGBA8:
                            binarizer.Add((byte)pix.R);
                            binarizer.Add((byte)pix.G);
                            binarizer.Add((byte)pix.B);
                            binarizer.Add((byte)pix.A);
                            break;

                        case ResTex.FormatType.RGB8:
                            binarizer.Add((byte)pix.R);
                            binarizer.Add((byte)pix.G);
                            binarizer.Add((byte)pix.B);
                            break;

                        case ResTex.FormatType.RGB5A1:
                            binarizer.Add((ushort)(
                                  (((ushort)(pix.R & 0xF8)) << 8)
                                | (((ushort)(pix.G & 0xF8)) << 3)
                                | (((ushort)(pix.B & 0xF8)) >> 2)
                                | (((ushort)(pix.A & 0x80)) >> 7)
                                ));
                            break;

                        case ResTex.FormatType.RGBA4:
                            binarizer.Add((ushort)(
                                  (((ushort)(pix.R & 0xF0)) << 8)
                                | (((ushort)(pix.G & 0xF0)) << 4)
                                | (((ushort)(pix.B & 0xF0)))
                                | (((ushort)(pix.A & 0xF0)) >> 4)
                                ));
                            break;

                        case ResTex.FormatType.RGB565:
                            binarizer.Add((ushort)(
                                  (((ushort)(pix.R & 0xF8)) << 8)
                                | (((ushort)(pix.G & 0xFC)) << 3)
                                | (((ushort)(pix.B & 0xF8)) >> 3)
                                ));
                            break;

                        case ResTex.FormatType.R8:
                            binarizer.Add((byte)pix.R);
                            break;

                        case ResTex.FormatType.RG8:
                            binarizer.Add((byte)pix.R);
                            binarizer.Add((byte)pix.G);
                            break;
                                
                        default:
                            throw new Exception("Unsupported format type.");
                        }
                    }
                }
            }
        }

        //============================================================
        ResTex mRes;
    }
}
