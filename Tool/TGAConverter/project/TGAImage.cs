using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;

namespace CrossFramework.TGAConverter
{
    /// <summary>
    /// Tergaイメージクラス。
    /// </summary>
    class TGAImage
    {
        /// <summary>
        /// TGAファイルパスから作成する。
        /// </summary>
        /// <param name="aFilePath">ファイルパス。</param>
        /// <returns></returns>
        public static TGAImage FromFilePath(string aFilePath)
        {
            // ロード
            byte[] bytes = File.ReadAllBytes(aFilePath);

            // MemoryStream変換
            MemoryStream stream = new MemoryStream(bytes);

            // 作成
            return new TGAImage(new Reader(new BinaryReader(stream)));
        }

        /// <summary>
        /// アルファチャンネルがあるか。
        /// </summary>
        public bool IsAlphaPixelFormat { get { return mHeader.BitsPerPixel == 32; } }

        /// <summary>
        /// イメージとして取得。
        /// </summary>
        public Image Image
        {
            get
            {
                Bitmap bmp = new Bitmap(mHeader.Width, mHeader.Height);
                for ( int y = 0; y < mHeader.Height; ++y )
                {
                    for ( int x = 0; x < mHeader.Width; ++x )
                    {
                        bmp.SetPixel(x,y, mPixels[x,y]);
                    }
                }
                return bmp;
            }
        }

        //============================================================
        struct Header
        {
            public const int Size = 18;
            public byte IdLength;
            public byte ColorMapType;
            public byte DataTypeCode;
            public byte ColorMapElement1;
            public uint ColorMapElement2;
            public ushort XOrigin;
            public ushort YOrigin;
            public ushort Width;
            public ushort Height;
            public byte BitsPerPixel;
            public byte ImageDescriptor;
        };

        class Reader
        {
            public Reader(BinaryReader aReader)
            {
                mReader = aReader;
            }

            public byte ReadByte()
            {
                return mReader.ReadByte();
            }

            public ushort ReadUInt16()
            {
                if (BitConverter.IsLittleEndian)
                {
                    return mReader.ReadUInt16();
                }
                else
                {
                    byte[] bytes = mReader.ReadBytes(2);
                    Array.Reverse(bytes);
                    return BitConverter.ToUInt16(bytes, 0);
                }
            }

            public uint ReadUInt32()
            {
                if (BitConverter.IsLittleEndian)
                {
                    return mReader.ReadUInt32();
                }
                else
                {
                    byte[] bytes = mReader.ReadBytes(4);
                    Array.Reverse(bytes);
                    return BitConverter.ToUInt32(bytes, 0);
                }
            }

            //============================================================
            readonly BinaryReader mReader;
        };
        
        class NotSupportedDataException : Exception
        {
            public NotSupportedDataException()
                : base( "This tga data is not supported." )
            {
            }
        };
        //============================================================
        Header  mHeader;
        Color[,] mPixels;

        //============================================================
        TGAImage(Reader aReader)
        {
            // ヘッダ解析
            {
                // 読み込み
                Header h;
                h.IdLength = aReader.ReadByte();
                h.ColorMapType = aReader.ReadByte();
                h.DataTypeCode = aReader.ReadByte();
                h.ColorMapElement1 = aReader.ReadByte();
                h.ColorMapElement2 = aReader.ReadUInt32();
                h.XOrigin = aReader.ReadUInt16();
                h.YOrigin = aReader.ReadUInt16();
                h.Width = aReader.ReadUInt16();
                h.Height = aReader.ReadUInt16();
                h.BitsPerPixel = aReader.ReadByte();
                h.ImageDescriptor = aReader.ReadByte();

                // サポートチェック
                if (h.IdLength != 0)
                {
                    throw new NotSupportedDataException();
                }
                if (h.ColorMapType != 0)
                {
                    throw new NotSupportedDataException();
                }
                if (h.DataTypeCode != 2)
                {
                    throw new NotSupportedDataException();
                }
                if (h.ColorMapElement1 != 0)
                {
                    throw new NotSupportedDataException();
                }
                if (h.ColorMapElement2 != 0)
                {
                    throw new NotSupportedDataException();
                }
                if (h.XOrigin != 0)
                {
                    throw new NotSupportedDataException();
                }
                if (h.YOrigin != 0)
                {
                    throw new NotSupportedDataException();
                }
                if (h.Width == 0)
                {
                    throw new NotSupportedDataException();
                }
                if (h.Height == 0)
                {
                    throw new NotSupportedDataException();
                }
                switch (h.BitsPerPixel)
                {
                    case 24:
                        if (h.ImageDescriptor != 0)
                        {
                            throw new NotSupportedDataException();
                        }
                        break;

                    case 32:
                        if (h.ImageDescriptor != 8)
                        {
                            throw new NotSupportedDataException();
                        }
                        break;

                    default:
                        throw new NotSupportedDataException();
                }

                // OK
                mHeader = h;
            }

            // ピクセル解析
            mPixels = new Color[mHeader.Width, mHeader.Height];
            for (uint srcY = 0; srcY < mHeader.Height; ++srcY)
            {
                uint dstY = (uint)(mHeader.Height - 1 - srcY);
                for (uint srcX = 0; srcX < mHeader.Width; ++srcX)
                {
                    uint dstX = srcX;
                    byte b = aReader.ReadByte();
                    byte g = aReader.ReadByte();
                    byte r = aReader.ReadByte();
                    byte a = 255;
                    if ( IsAlphaPixelFormat )
                    {
                        a = aReader.ReadByte();
                    }
                    mPixels[dstX, dstY] = Color.FromArgb(a,r,g,b);
                }
            }
        }
    }
}
