using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;
using System.Reflection;
using System.Xml.Schema;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// xtexファイル。
    /// </summary>
    public class ResTex
    {
        //============================================================

        /// <summary>
        /// メジャーバージョン番号。
        /// </summary>
        public const byte VersionMajor = 0;

        /// <summary>
        /// マイナーバージョン番号。
        /// </summary>
        public const byte VersionMinor = 0;

        //============================================================
        /// <summary>
        /// ピクセルフォーマット。
        /// </summary>
        public enum FormatType
        {
            /// <summary>
            /// RGBA8。
            /// </summary>
            RGBA8,

            /// <summary>
            /// RGB8。
            /// </summary>
            RGB8,

            /// <summary>
            /// RGB5A1。
            /// </summary>
            RGB5A1,

            /// <summary>
            /// RGBA4。
            /// </summary>
            RGBA4,
            
            /// <summary>
            /// RGB565。
            /// </summary>
            RGB565,


            /// <summary>
            /// A8。
            /// </summary>
            A8,

            /// <summary>
            /// LA8。
            /// </summary>
            LA8,

            /// <summary>
            /// L8。
            /// </summary>
            L8,
        };
        /// <summary>
        /// アルファがあるフォーマットか。
        /// </summary>
        /// <param name="aType"></param>
        /// <returns></returns>
        static public bool HasAlpha(FormatType aType)
        {
            switch (aType)
            {
                case FormatType.RGBA8:
                case FormatType.RGB5A1:
                case FormatType.RGBA4:
                case FormatType.A8:
                case FormatType.LA8:
                    return true;

                default:
                    return false;
            }
        }

        /// <summary>
        /// RGBがあるフォーマットか。
        /// </summary>
        /// <param name="aType"></param>
        /// <returns></returns>
        static public bool HasRGB(FormatType aType)
        {
            switch (aType)
            {
                case FormatType.RGBA8:
                case FormatType.RGB5A1:
                case FormatType.RGBA4:
                case FormatType.RGB8:
                case FormatType.RGB565:
                    return true;

                default:
                    return false;
            }
        }

        /// <summary>
        /// Luminanceがあるフォーマットか。
        /// </summary>
        /// <param name="aType"></param>
        /// <returns></returns>
        static public bool HasLuminance(FormatType aType)
        {
            switch (aType)
            {
                case FormatType.LA8:
                case FormatType.L8:
                    return true;

                default:
                    return false;
            }
        }

        //============================================================
        /// <summary>
        /// Imageオブジェクトから作成。
        /// </summary>
        /// <param name="aImage"></param>
        /// <param name="aFormat">ピクセルフォーマット。</param>
        /// <param name="aName">イメージの名前。通常は拡張子を抜いたファイル名を指定する。</param>
        static public ResTex FromImage(Image aImage, FormatType aFormat, string aName)
        {
            return new ResTex(aImage, aFormat, aName);
        }

        /// <summary>
        /// XMLファイルから作成。
        /// </summary>
        /// <returns></returns>
        static public ResTex FromXml(XmlDocument aXML, FileInfo aFileInfo)
        {
            // 名前
            string name = aFileInfo.Name.Substring(0, aFileInfo.Name.Length - aFileInfo.Extension.Length);

            // 作成
            return new ResTex(aXML.DocumentElement, aXML.NameTable, name);
        }

        /// <summary>
        /// XMLファイルから作成。
        /// </summary>
        /// <param name="aFilePath"></param>
        /// <returns></returns>
        static public ResTex FromXml(string aFilePath)
        {
            // 設定作成
            XmlReaderSettings setting = new XmlReaderSettings();
            setting.ValidationType = ValidationType.Schema;
            {// スキーマ登録
                string schemaPath = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location) + @"/CrossFramework.XG3D.XTEX.xsd";
                XmlSchemaSet schemaSet = new XmlSchemaSet();
                schemaSet.Add(null,schemaPath);
                setting.Schemas = schemaSet;
            }

            // XMLロード
            FileInfo fileInfo = new FileInfo(aFilePath);
            XmlDocument xml = new XmlDocument();
            xml.Load(XmlReader.Create(fileInfo.FullName, setting));

            // 作成
            return FromXml(xml, fileInfo);
        }

        //============================================================

        /// <summary>
        /// 名前。
        /// </summary>
        public string Name { get { return mName; } }

        /// <summary>
        /// 横ピクセル数。
        /// </summary>
        public ushort Width { get { return mWidth; } }

        /// <summary>
        /// 縦ピクセル数。
        /// </summary>
        public ushort Height { get { return mHeight; } }
        
        /// <summary>
        /// テクスチャフォーマット。
        /// </summary>
        public FormatType Format { get { return mFormat; } }
        
        //============================================================
        /// <summary>
        /// 指定の位置のピクセル値を取得する。
        /// 位置は左下が原点。
        /// </summary>
        /// <param name="aX"></param>
        /// <param name="aY"></param>
        /// <returns></returns>
        public Color Pixel(ushort aX, ushort aY)
        {
            return mPixels[aX, aY];
        }

        /// <summary>
        /// XML形式で書き出す。
        /// </summary>
        /// <param name="aFilePath"></param>
        public void WriteXml(string aFilePath)
        {
            using (MemoryStream mem = new MemoryStream())
            {
                // 設定作成
                XmlWriterSettings setting = new XmlWriterSettings();
                setting.Indent = true;
                setting.IndentChars = "    ";
                setting.NewLineChars = sNewLineChars;

                // XML作成
                using (XmlWriter xml = XmlWriter.Create(mem, setting))
                {
                    // elem
                    xml.WriteStartElement("xtex",@"http://www.10106.net/crossframework/Schema/XG3D/XTEX");
                    {
                        // attr
                        xml.WriteAttributeString("version_major", VersionMajor.ToString());
                        xml.WriteAttributeString("version_minor", VersionMinor.ToString());

                        // elem
                        xml.WriteStartElement("body");
                        {
                            // attr
                            xml.WriteAttributeString("width", Width.ToString());
                            xml.WriteAttributeString("height", Height.ToString());
                            xml.WriteAttributeString("format", Format.ToString());
                            
                            // elem
                            xml.WriteStartElement("pixels");
                            {
                                bool hasRGB = HasRGB(mFormat);
                                bool hasLuminance = HasLuminance(mFormat);
                                bool hasAlpha = HasAlpha(mFormat);
                                for (int y = 0; y < mHeight; ++y)
                                {
                                    for (int x = 0; x < mWidth; ++x)
                                    {
                                        // pixel取得
                                        Color pix = mPixels[x, y];

                                        // string 作成
                                        string str = "";
                                        if (hasRGB)
                                        {
                                            str += pix.R.ToString() + " " + pix.G.ToString() + " " + pix.B.ToString();
                                        }
                                        if (hasLuminance)
                                        {
                                            str += pix.R.ToString();
                                        }
                                        if (hasAlpha)
                                        {
                                            if (str.Length != 0)
                                            {
                                                str += " ";
                                            }
                                            str += pix.A.ToString();
                                        }

                                        // 書き込み
                                        xml.WriteString(str + setting.NewLineChars);
                                    }
                                }
                            }
                            xml.WriteEndElement();
                        }
                        xml.WriteEndElement();
                    }
                    xml.WriteEndDocument();
                }

                // 書き出し
                File.WriteAllBytes(aFilePath, mem.ToArray());
            }
        }

        //============================================================
        const string sNewLineChars = "\r\n";

        //============================================================
        static int compressB1(int aValue)
        {
            return 0x80 <= aValue ? 0xFF : 0;
        }

        static int compressB4(int aValue)
        {
            int baseValue = (aValue & 0xF0);
            return baseValue + ( baseValue >> 4 );
        }

        static int compressB5(int aValue)
        {
            int baseValue = (aValue & 0xF8);
            return baseValue + ( baseValue >> 5 );
        }

        static int compressB6(int aValue)
        {
            int baseValue = (aValue & 0xFC);
            return baseValue + ( baseValue >> 6 );
        }

        static int calcLuminance(Color aPix)
        {
            return (((int)aPix.R) + ((int)aPix.G) + ((int)aPix.B)) / 3;
        }

        //============================================================
        string mName;
        ushort mWidth;
        ushort mHeight;
        FormatType mFormat;
        Color[,] mPixels;

        //============================================================
        ResTex(Image aImage, FormatType aFormat, string aName)
        {
            // コピー
            mName = aName;
            mWidth = (ushort)aImage.Width;
            mHeight = (ushort)aImage.Height;
            mFormat = aFormat;
            mPixels = new Color[mWidth, mHeight];

            // 設定
            Bitmap bmp = new Bitmap(aImage);
            for (int y = 0; y < mHeight; ++y)
            {
                int srcY = mHeight - 1 - y;
                for (int x = 0; x < mWidth; ++x)
                {
                    Color srcPix = bmp.GetPixel(x, srcY);
                    Color newPix = srcPix;
                    switch (aFormat)
                    {
                        case FormatType.RGBA8:
                            break;

                        case FormatType.RGB8:
                            newPix = Color.FromArgb(255, srcPix.R, srcPix.G, srcPix.B);
                            break;

                        case FormatType.RGB5A1:
                            newPix = Color.FromArgb(
                                compressB1(srcPix.A)
                                , compressB5(srcPix.R)
                                , compressB5(srcPix.G)
                                , compressB5(srcPix.B)
                                );
                            break;

                        case FormatType.RGBA4:
                            newPix = Color.FromArgb(
                                compressB4(srcPix.A)
                                , compressB4(srcPix.R)
                                , compressB4(srcPix.G)
                                , compressB4(srcPix.B)
                                );
                            break;

                        case FormatType.RGB565:
                            newPix = Color.FromArgb(
                                255
                                , compressB5(srcPix.R)
                                , compressB6(srcPix.G)
                                , compressB5(srcPix.B)
                                );
                            break;

                        case FormatType.A8:
                            newPix = Color.FromArgb(
                                srcPix.A
                                , 255
                                , 255
                                , 255
                                );
                            break;

                        case FormatType.LA8:
                            {
                                int ave = calcLuminance(srcPix);
                                newPix = Color.FromArgb(
                                    srcPix.A
                                    , ave
                                    , ave
                                    , ave
                                    );
                            }
                            break;

                        case FormatType.L8:
                            {
                                int ave = calcLuminance(srcPix);
                                newPix = Color.FromArgb(
                                    255
                                    , ave
                                    , ave
                                    , ave
                                    );
                            }
                            break;
                            
                        default:
                            throw new Exception("Unsupported format type.");
                    }
                    mPixels[x, y] = newPix;
                }
            }
        }

        //------------------------------------------------------------
        ResTex(XmlNode aXml,XmlNameTable aNameTable, string aName)
        {
            // NameTableセットアップ
            XmlNamespaceManager nsMgr = new XmlNamespaceManager(aNameTable);
            nsMgr.AddNamespace("n", aXml.NamespaceURI); // n: に割り当て。

            // 取得
            XmlNode xnBody = aXml.SelectSingleNode("./n:body", nsMgr);
            mName = aName;
            mWidth = ushort.Parse(xnBody.Attributes.GetNamedItem("width").Value);
            mHeight = ushort.Parse(xnBody.Attributes.GetNamedItem("height").Value);
            mFormat = (FormatType)Enum.Parse(typeof(FormatType), xnBody.Attributes.GetNamedItem("format").Value);

            // ピクセル
            XmlNode xnPixels = xnBody.SelectSingleNode("./n:pixels", nsMgr);
            string[] entries = xnPixels.InnerText.Replace("\r\n", " ").Replace('\n',' ').Trim().Split(' ');
            mPixels = new Color[mWidth, mHeight];
            {
                int idx = 0;
                for (int y = 0; y < mHeight; ++y)
                {
                    for (int x = 0; x < mWidth; ++x)
                    {
                        byte r = 255;
                        byte g = 255; 
                        byte b = 255; 
                        byte a = 255;

                        if (HasRGB(mFormat))
                        {// RGB
                            r = byte.Parse(entries[idx]); ++idx;
                            g = byte.Parse(entries[idx]); ++idx;
                            b = byte.Parse(entries[idx]); ++idx;
                        }
                        if (HasLuminance(mFormat))
                        {// Luminance
                            r = byte.Parse(entries[idx]); ++idx;
                            g = r;
                            b = r;
                        }
                        if (HasAlpha(mFormat))
                        {// Alpha
                            a = byte.Parse(entries[idx]); ++idx;
                        }
                        mPixels[x, y] = Color.FromArgb(a, r, g, b);
                    }
                }
            }
        }
    }
}
