using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;

namespace CrossFramework
{
    /// <summary>
    /// XDataXML���o�C�i���f�[�^�ɕϊ�����B
    /// </summary>
    public class XDataConverter
    {
        /// <summary>
        /// �G���f�B�A���̎�ށB
        /// </summary>
        public enum Endian
        {
            /// <summary>
            /// LittleEndian�B
            /// </summary>
            Little, 

            /// <summary>
            /// BigEndian�B
            /// </summary>
            Big,   
        };

        /// <summary>
        /// �ϊ��I�v�V�����B
        /// </summary>
        public class Option
        {
            /// <summary>
            /// �o�̓f�[�^�̃G���f�B�A���B�f�t�H���g��LittleEndian�B
            /// </summary>
            public Endian OutputEndian = Endian.Little; 

            /// <summary>
            /// �o�̓f�[�^�̕�����̃G���R�[�_�B�f�t�H���g��UTF8�B
            /// </summary>
            public Encoding Encoding = Encoding.UTF8;

            /// <summary>
            /// true�̏ꍇ�A���x�������Ɏ��s���Ă��G���[�ɂ��Ȃ��B
            /// </summary>
            public bool IgnoreLabelNotFoundError = false;

            /// <summary>
            /// true�̏ꍇ�A�G���[���Ȃ���Ή����R���\�[���ɏo�͂��Ȃ��B
            /// </summary>
            public bool IsSilent = false;
        };

        /// <summary>
        /// �C�ӂ̃f�[�^��XData�Ƃ��ăo�C�i�������邽�߂̃N���X�B
        /// </summary>
        public class Binarizer
        {
            //============================================================
            /// <summary>
            /// �R���X�g���N�^�B
            /// </summary>
            /// <param name="aOption"></param>
            public Binarizer(Option aOption)
            {
                mImpl = new CrossFramework.Binarizer(aOption);
            }

            /// <summary>
            /// �S�v�f�̒ǉ����I������炱����ĂсA�o�C�i�����ʂ��擾����B
            /// </summary>
            /// <returns></returns>
            public byte[] Finish()
            {
                return mImpl.Finish();
            }

            /// <summary>
            /// ���݈ʒu�̃A���C�����g�̎w��B
            /// </summary>
            /// <param name="aAlign"></param>
            public void AddAlign(uint aAlign)
            {
                mImpl.AddAlign(aAlign);
            }

            /// <summary>
            /// ���x���̒ǉ��B
            /// </summary>
            /// <param name="aLabel"></param>
            public void AddLabel(string aLabel)
            {
                mImpl.AddLabel(aLabel);
            }

            /// <summary>
            /// �Q�Ƃ̒ǉ��B
            /// </summary>
            /// <param name="aLabel"></param>
            public void AddReference(string aLabel)
            {
                mImpl.AddReference(aLabel);
            }

            /// <summary>
            /// ��̎Q�Ƃ̒ǉ��B
            /// </summary>
            public void AddNullReference()
            {
                Add((int)0);
            }

            /// <summary>
            /// ������̒ǉ��B
            /// </summary>
            /// <param name="aStr"></param>
            public void AddString(string aStr)
            {
                mImpl.AddString(aStr);
            }

            /// <summary>
            /// ������Q�Ƃ̒ǉ��B
            /// </summary>
            /// <param name="aStr"></param>
            public void AddStringRef(string aStr)
            {
                mImpl.AddStringRef(aStr);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aVal"></param>
            public void Add(sbyte aVal)
            {
                mImpl.Add(aVal);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aVal"></param>
            public void Add(short aVal)
            {
                mImpl.Add(aVal);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aVal"></param>
            public void Add(int aVal)
            {
                mImpl.Add(aVal);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aVal"></param>
            public void Add(long aVal)
            {
                mImpl.Add(aVal);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aVal"></param>
            public void Add(byte aVal)
            {
                mImpl.Add(aVal);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aVal"></param>
            public void Add(ushort aVal)
            {
                mImpl.Add(aVal);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aVal"></param>
            public void Add(uint aVal)
            {
                mImpl.Add(aVal);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aVal"></param>
            public void Add(ulong aVal)
            {
                mImpl.Add(aVal);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aVal"></param>
            public void Add(float aVal)
            {
                mImpl.Add(aVal);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aVal"></param>
            public void Add(double aVal)
            {
                mImpl.Add(aVal);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aArr"></param>
            public void Add(sbyte[] aArr)
            {
                mImpl.Add(aArr);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aArr"></param>
            public void Add(short[] aArr)
            {
                mImpl.Add(aArr);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aArr"></param>
            public void Add(int[] aArr)
            {
                mImpl.Add(aArr);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aArr"></param>
            public void Add(long[] aArr)
            {
                mImpl.Add(aArr);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aArr"></param>
            public void Add(byte[] aArr)
            {
                mImpl.Add(aArr);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aArr"></param>
            public void Add(ushort[] aArr)
            {
                mImpl.Add(aArr);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aArr"></param>
            public void Add(uint[] aArr)
            {
                mImpl.Add(aArr);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aArr"></param>
            public void Add(ulong[] aArr)
            {
                mImpl.Add(aArr);
            }

            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aArr"></param>
            public void Add(float[] aArr)
            {
                mImpl.Add(aArr);
            }
            
            /// <summary>
            /// �l�̒ǉ��B
            /// </summary>
            /// <param name="aArr"></param>
            public void Add(double[] aArr)
            {
                mImpl.Add(aArr);
            }        

            //============================================================
            CrossFramework.Binarizer mImpl;
        };

        /// <summary>
        /// XML�e�L�X�g��������o�C�i���f�[�^�ɕϊ�����B
        /// </summary>
        /// <param name="aXMLText">XML�e�L�X�g������B</param>
        /// <param name="aOption">�ϊ��I�v�V�����B</param>
        /// <returns>�ϊ����ꂽ�o�C�i���f�[�^�B</returns>
        static public byte[] Convert(string aXMLText, Option aOption)
        {            
            // ���s
            return CrossFramework.Binarizer.Exec(
                new XmlTextReader(new StringReader(aXMLText))
                , aOption
                , null
                , null
                );
        }

        /// <summary>
        /// XML�e�L�X�g��������o�C�i���f�[�^�ɕϊ����t�@�C���ɏo�͂���B
        /// </summary>
        /// <param name="aXMLText">XML�e�L�X�g������B</param>
        /// <param name="aOption">�ϊ��I�v�V�����B</param>
        /// <param name="aOutputFile">�o�̓t�@�C���B</param>
        /// <returns>�ϊ����ꂽ�o�C�i���f�[�^�B</returns>
        static public byte[] Convert(string aXMLText, Option aOption, FileInfo aOutputFile)
        {
            // �`�F�b�N
            outputFileNullCheck(aOutputFile);
            
            // ���s
            return CrossFramework.Binarizer.Exec(
                new XmlTextReader(new StringReader(aXMLText))
                , aOption
                , null
                , aOutputFile
                );
        }

        /// <summary>
        /// XML�t�@�C�����o�C�i���f�[�^�ɕϊ�����B
        /// </summary>
        /// <param name="aInputFile">���͂ƂȂ�XML�t�@�C���B</param>
        /// <param name="aOption">�ϊ��I�v�V�����B</param>
        /// <returns>�ϊ����ꂽ�o�C�i���f�[�^�B</returns>
        static public byte[] Convert(FileInfo aInputFile, Option aOption)
        {
            // ���s
            return CrossFramework.Binarizer.Exec(
                new XmlTextReader(aInputFile.FullName)
                , aOption
                , aInputFile
                , null
                );
        }

        /// <summary>
        /// XML�t�@�C�����o�C�i���f�[�^�ɕϊ����t�@�C���ɏo�͂���B
        /// </summary>
        /// <param name="aInputFile">���͂ƂȂ�XML�t�@�C���B</param>
        /// <param name="aOption">�ϊ��I�v�V�����B</param>
        /// <param name="aOutputFile">�o�̓t�@�C���B</param>
        /// <returns>�ϊ����ꂽ�o�C�i���f�[�^�B</returns>
        static public byte[] Convert(FileInfo aInputFile, Option aOption, FileInfo aOutputFile)
        {
            // �`�F�b�N
            outputFileNullCheck(aOutputFile);

            // ���s
            return CrossFramework.Binarizer.Exec(
                new XmlTextReader(aInputFile.FullName)
                , aOption
                , aInputFile
                , aOutputFile
                );
        }

        //============================================================

        // �o��FileInfo��null���ǂ����`�F�b�N����B
        static void outputFileNullCheck(FileInfo aOutputFile)
        {
            if (aOutputFile == null)
            {
                new System.Exception("aOutputFile ��null�ł��B");
            }
        }

        XDataConverter(){} // �A�N�Z�X�֎~�B

    }

    // ���x���Q�Ə��B
    class LabelReference
    {
        public readonly string Label;
        public readonly int Offset;

        public LabelReference(string aLabel, long aOffset)
        {
            Label = aLabel;
            Offset = (int)aOffset;
        }
    };

    // �o�C�i���ϊ��B
    class Binarizer
    {
        //============================================================
        public static void PrintBanner()
        {
            Console.WriteLine("[XData Converter] Program Version '" + System.Reflection.Assembly.GetExecutingAssembly().GetName().Version + "' Format Version '" + FORMAT_MAJOR_VERSION + "." + FORMAT_MINOR_VERSION + "'");
        }
        
        //------------------------------------------------------------
        public static byte[] Exec(
            XmlReader aXml
            , XDataConverter.Option aOption
            , FileInfo aInputFile
            , FileInfo aOutputFile
            )
        {

            // ���\��
            if (!aOption.IsSilent)
            {
                Binarizer.PrintBanner();
                if (aInputFile != null)
                {
                    Console.WriteLine("Input  : " + aInputFile);
                }
                if (aOutputFile != null)
                {
                    Console.WriteLine("Output : " + aOutputFile);
                }
                Console.WriteLine("Endian : " + aOption.OutputEndian);
                Console.WriteLine("Encode : " + aOption.Encoding.WebName);
            }

            // �o�C�i���Y
            var obj = new Binarizer(aOption);
            obj.AddXml(aXml);

            // �t�@�C���o��
            if (aOutputFile != null)
            {
                File.WriteAllBytes(aOutputFile.FullName, obj.result);
            }

            // Finish
            if (!aOption.IsSilent)
            {
                Console.WriteLine("Done! Data size is '" + obj.result.Length + "'.");
            }

            // ���ʂ�Ԃ�
            return obj.result;
        }

        //============================================================
        public Binarizer(XDataConverter.Option aOption)
        {
            // �����o�ϐ�������
            option = aOption;
            memoryStream = new MemoryStream();
            binaryWriter = new BinaryWriter(memoryStream, option.Encoding);

            // �w�b�_�̏�������
            binaryWriter.Write(new byte[] { 0x58, 0x42, 0x49, 0x4E }); // signature
            binaryWriter.Write(bytes(BitConverter.GetBytes((UInt16)0x1234))); // endian
            binaryWriter.Write(FORMAT_MAJOR_VERSION); // major version
            binaryWriter.Write(FORMAT_MINOR_VERSION); // minor version
            binaryWriter.Write(bytes(BitConverter.GetBytes((UInt32)0))); // datasize
            binaryWriter.Write(bytes(BitConverter.GetBytes((UInt32)option.Encoding.CodePage))); // codePage
        }

        //============================================================
        public void AddAlign(uint aAlign)
        {
            processAlign(aAlign);
        }
        public void AddLabel(string aLabel)
        {
            processLabel(aLabel);
        }
        public void AddReference(string aLabel)
        {
            processReference(aLabel);
        }
        public void AddString(string aStr)
        {
            processString(aStr);
        }
        public void AddStringRef(string aStr)
        {
            processStringRef(aStr);
        }
        public void Add(sbyte aVal)
        {
            binaryWriter.Write(aVal);
        }
        public void Add(short aVal)
        {
            binaryWriter.Write(aVal);
        }
        public void Add(int aVal)
        {
            binaryWriter.Write(aVal);
        }
        public void Add(long aVal)
        {
            binaryWriter.Write(aVal);
        }
        public void Add(byte aVal)
        {
            binaryWriter.Write(aVal);
        }
        public void Add(ushort aVal)
        {
            binaryWriter.Write(aVal);
        }
        public void Add(uint aVal)
        {
            binaryWriter.Write(aVal);
        }
        public void Add(ulong aVal)
        {
            binaryWriter.Write(aVal);
        }
        public void Add(float aVal)
        {
            binaryWriter.Write(aVal);
        }
        public void Add(double aVal)
        {
            binaryWriter.Write(aVal);
        }
        public void Add(sbyte[] aArr)
        {
            foreach (var val in aArr)
            {
                Add(val);
            }
        }
        public void Add(short[] aArr)
        {
            foreach (var val in aArr)
            {
                Add(val);
            }
        }
        public void Add(int[] aArr)
        {
            foreach (var val in aArr)
            {
                Add(val);
            }
        }
        public void Add(long[] aArr)
        {
            foreach (var val in aArr)
            {
                Add(val);
            }
        }
        public void Add(byte[] aArr)
        {
            foreach (var val in aArr)
            {
                Add(val);
            }
        }
        public void Add(ushort[] aArr)
        {
            foreach (var val in aArr)
            {
                Add(val);
            }
        }
        public void Add(uint[] aArr)
        {
            foreach (var val in aArr)
            {
                Add(val);
            }
        }
        public void Add(ulong[] aArr)
        {
            foreach (var val in aArr)
            {
                Add(val);
            }
        }
        public void Add(float[] aArr)
        {
            foreach (var val in aArr)
            {
                Add(val);
            }
        }
        public void Add(double[] aArr)
        {
            foreach (var val in aArr)
            {
                Add(val);
            }
        }
        
        //------------------------------------------------------------
        public byte[] Finish()
        {
            // string_ref�̎��̂�ǉ�
            for (int i = 0; i < autoStringEntityArray.Count; ++i)
            {
                // align�͎����Œǉ�
                processAlign(4);

                // ���x���ǉ�
                processLabel(createStringRefLabel(i));

                // ���̂�ǉ�
                processString((string)autoStringEntityArray[i]);
            }

            // �f�[�^�T�C�Y
            UInt32 dataSize = (uint)binaryWriter.Seek(0, SeekOrigin.Current);
            binaryWriter.Seek(8, SeekOrigin.Begin);
            binaryWriter.Write(bytes(BitConverter.GetBytes(dataSize)));

            // ���x������
            foreach (LabelReference labelRef in labelReferenceArray)
            {
                if (labelTable[labelRef.Label] == null)
                {// ���x�����Ȃ��̂Ńp�X
                    if (!option.IgnoreLabelNotFoundError)
                    {
                        throw new Exception("Not found label named '" + labelRef.Label + "'");
                    }
                    continue;
                }
                binaryWriter.Seek(labelRef.Offset, SeekOrigin.Begin);
                binaryWriter.Write(bytes(BitConverter.GetBytes((UInt32)labelTable[labelRef.Label])));
            }

            // �o�C�i���f�[�^�ɏo��
            result = memoryStream.ToArray();
            return result;
        }

        //============================================================
        // �^�O�̎��
        enum TagKind
        {
            Align,
            Label,
            Reference,
            SInt8,
            SInt16,
            SInt32,
            SInt64,
            SInt8Array,
            SInt16Array,
            SInt32Array,
            SInt64Array,
            UInt8,
            UInt16,
            UInt32,
            UInt64,
            UInt8Array,
            UInt16Array,
            UInt32Array,
            UInt64Array,
            Float32,
            Float64,
            Float32Array,
            Float64Array,
            String,
            StringRef,
        };

        //============================================================
        const Byte FORMAT_MAJOR_VERSION = 2; // ���W���[�o�[�W�����ԍ��B
        const Byte FORMAT_MINOR_VERSION = 0; // �}�C�i�[�o�[�W�����ԍ��B

        // ���s���̃G���f�B�A���B
        static XDataConverter.Endian machineEndian = BitConverter.IsLittleEndian
            ? XDataConverter.Endian.Little
            : XDataConverter.Endian.Big;

        // �z��̋�؂蕶���B
        static char[] ARRAY_SPLIT_CHARS = new char[] { ' ' };
        
        // TAG�����B
        static Dictionary<string, TagKind> sTagDictionary = createTagDictionary();
        static Dictionary<string, TagKind> createTagDictionary()
        {
            Dictionary<string, TagKind> tagDictionary = new Dictionary<string, TagKind>();
            tagDictionary.Add("align", TagKind.Align);
            tagDictionary.Add("label", TagKind.Label);
            tagDictionary.Add("reference", TagKind.Reference);
            tagDictionary.Add("sint8", TagKind.SInt8);
            tagDictionary.Add("sint16", TagKind.SInt16);
            tagDictionary.Add("sint32", TagKind.SInt32);
            tagDictionary.Add("sint64", TagKind.SInt64);
            tagDictionary.Add("sint8_array", TagKind.SInt8Array);
            tagDictionary.Add("sint16_array", TagKind.SInt16Array);
            tagDictionary.Add("sint32_array", TagKind.SInt32Array);
            tagDictionary.Add("sint64_array", TagKind.SInt64Array);
            tagDictionary.Add("uint8", TagKind.UInt8);
            tagDictionary.Add("uint16", TagKind.UInt16);
            tagDictionary.Add("uint32", TagKind.UInt32);
            tagDictionary.Add("uint64", TagKind.UInt64);
            tagDictionary.Add("uint8_array", TagKind.UInt8Array);
            tagDictionary.Add("uint16_array", TagKind.UInt16Array);
            tagDictionary.Add("uint32_array", TagKind.UInt32Array);
            tagDictionary.Add("uint64_array", TagKind.UInt64Array);
            tagDictionary.Add("float32", TagKind.Float32);
            tagDictionary.Add("float64", TagKind.Float64);
            tagDictionary.Add("float32_array", TagKind.Float32Array);
            tagDictionary.Add("float64_array", TagKind.Float64Array);
            tagDictionary.Add("string", TagKind.String);
            tagDictionary.Add("string_ref", TagKind.StringRef);
            return tagDictionary;
        }

        //============================================================
        // ����
        byte[] result;

        // �ҏW�Ɏg���ϐ�
        XDataConverter.Option option;
        Hashtable labelTable = new Hashtable();
        ArrayList labelReferenceArray = new ArrayList();
        ArrayList autoStringEntityArray = new ArrayList();
        MemoryStream memoryStream = null;
        BinaryWriter binaryWriter = null;
        
        //============================================================
        void AddXml(XmlReader aXML)
        {
            // XML�쐬
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load(aXML);

            // ���[�g�`�F�b�N
            if (xmlDoc.DocumentElement.Name != "xdata_root")
            {
                throw new Exception("Root node name is not equal 'xdata_root'." + xmlDoc.DocumentElement.Name);
            }

            // �o�[�W�����`�F�b�N
            {
                XmlAttributeCollection attrs = xmlDoc.DocumentElement.Attributes;
                checkAttributeEqual(attrs, "major_version", FORMAT_MAJOR_VERSION.ToString());
                checkAttributeLessEqual(attrs, "minor_version", FORMAT_MINOR_VERSION);
            }

            // �e�^�O�̏���
            foreach (XmlNode node in xmlDoc.DocumentElement.ChildNodes)
            {
                // NodeType
                if (node.NodeType == XmlNodeType.Comment)
                {// �R�����g�̓p�X
                    continue;
                }
                else if (node.NodeType != XmlNodeType.Element)
                {// �����܂���
                    throw new Exception("Node named '" + node.Name + "' 's type is '" + node.NodeType.ToString() + "' not 'Element'.");
                }

                // NodeName
                TagKind tagKind;
                try
                {
                    tagKind = sTagDictionary[node.Name];
                }
                catch (Exception)
                {
                    throw new Exception("Unknown element name '" + node.Name + "'.");
                }
                switch(tagKind)
                {
                    case TagKind.Align:
                        {
                            uint alignValue = strToUInt32(nodeValue(node));
                            if (alignValue == 0)
                            {
                                throw new Exception("Illegal alignment value '" + alignValue + "'");
                            }
                            processAlign(alignValue);
                        }
                        break;

                    case TagKind.Label:
                        {
                            processLabel(
                                checkAttributeExist(node.Attributes, "name").Value
                                );
                        }
                        break;

                    case TagKind.Reference:
                        {
                            processReference(
                                checkAttributeExist(node.Attributes, "label_name").Value
                                );
                        }
                        break;

                    case TagKind.SInt8:
                        {
                            binaryWriter.Write(strToSInt8(nodeValue(node)));
                        }
                        break;
                    
                    case TagKind.SInt8Array:
                        {
                            foreach (string str in arrayToStringArray(node))
                            {
                                binaryWriter.Write(strToSInt8(str));
                            }
                        }
                        break;

                    case TagKind.SInt16:
                        {
                            binaryWriter.Write(strSInt16ToBytes(nodeValue(node)));
                        }
                        break;

                    case TagKind.SInt16Array:
                        {
                            foreach (string str in arrayToStringArray(node))
                            {
                                binaryWriter.Write(strSInt16ToBytes(str));
                            }
                        }
                        break;

                    case TagKind.SInt32:
                        {
                            binaryWriter.Write(strSInt32ToBytes(nodeValue(node)));
                        }
                        break;

                    case TagKind.SInt32Array:
                        {
                            foreach (string str in arrayToStringArray(node))
                            {
                                binaryWriter.Write(strSInt32ToBytes(str));
                            }
                        }
                        break;

                    case TagKind.SInt64:
                        {
                            binaryWriter.Write(strSInt64ToBytes(nodeValue(node)));
                        }
                        break;
                    
                    case TagKind.SInt64Array:
                        {
                            foreach (string str in arrayToStringArray(node))
                            {
                                binaryWriter.Write(strSInt64ToBytes(str));
                            }
                        }
                        break;

                    case TagKind.UInt8:
                        {
                            binaryWriter.Write(strToUInt8(nodeValue(node)));
                        }
                        break;
                            
                    case TagKind.UInt8Array:
                        {
                            foreach (string str in arrayToStringArray(node))
                            {
                                binaryWriter.Write(strToUInt8(str));
                            }
                        }
                        break;

                    case TagKind.UInt16:
                        {
                            binaryWriter.Write(strUInt16ToBytes(nodeValue(node)));
                        }
                        break;

                    case TagKind.UInt16Array:
                        {
                            foreach (string str in arrayToStringArray(node))
                            {
                                binaryWriter.Write(strUInt16ToBytes(str));
                            }
                        }
                        break;

                    case TagKind.UInt32:
                        {
                            binaryWriter.Write(strUInt32ToBytes(nodeValue(node)));
                        }
                        break;

                    case TagKind.UInt32Array:
                        {
                            foreach (string str in arrayToStringArray(node))
                            {
                                binaryWriter.Write(strUInt32ToBytes(str));
                            }
                        }
                        break;
                    
                    case TagKind.UInt64:
                        {
                            binaryWriter.Write(strUInt64ToBytes(nodeValue(node)));
                        }
                        break;

                    case TagKind.UInt64Array:
                        {
                            foreach (string str in arrayToStringArray(node))
                            {
                                binaryWriter.Write(strUInt64ToBytes(str));
                            }
                        }
                        break;

                    case TagKind.Float32:
                        {
                            binaryWriter.Write(strFloat32ToBytes(nodeValue(node)));
                        }
                        break;

                    case TagKind.Float32Array:
                        {
                            foreach (string str in arrayToStringArray(node))
                            {
                                binaryWriter.Write(strFloat32ToBytes(str));
                            }
                        }
                        break;

                    case TagKind.Float64:
                        {
                            binaryWriter.Write(strFloat64ToBytes(nodeValue(node)));
                        }
                        break;

                    case TagKind.Float64Array:
                        {
                            foreach (string str in arrayToStringArray(node))
                            {
                                binaryWriter.Write(strFloat64ToBytes(str));
                            }
                        }
                        break;

                    case TagKind.String:
                        {
                            processString(nodeValue(node));
                        }
                        break;

                    case TagKind.StringRef:
                        {
                            processStringRef(nodeValue(node));
                        }
                        break;

                    default:
                        System.Diagnostics.Debug.Assert(false);
                        break;
                }
            }
        }

        void writeLine(string str)
        {
            if (!option.IsSilent)
            {
                Console.WriteLine(str);
            }
        }

        void processAlign(uint alignValue)
        {
            long currentPos = binaryWriter.Seek(0, SeekOrigin.End);
            uint modResult = (uint)(currentPos % alignValue);
            if (0 < modResult)
            {
                for (uint i = modResult; i < alignValue; ++i)
                {
                    binaryWriter.Write((byte)0);
                }
            }
        }

        void processLabel(string labelStr)
        {
            if (labelTable[labelStr] != null)
            {
                throw new Exception("Label named '" + labelStr + "' is already exist.");
            }
            labelTable.Add(
                labelStr
                , (UInt32)binaryWriter.Seek(0, SeekOrigin.Current)
                );
        }

        void processReference(string labelStr)
        {
            labelReferenceArray.Add(new LabelReference(
                labelStr
                , binaryWriter.Seek(0, SeekOrigin.Current)
                ));
            binaryWriter.Write(BitConverter.GetBytes((UInt32)0));
        }

        void processString(string str)
        {
            binaryWriter.Write(strToBytes(str));
        }

        void processStringRef(string str)
        {
            // ���t�@�����X��ǉ�
            processReference(
                createStringRefLabel(autoStringEntityArray.Count)
                );

            // ���̂�����
            autoStringEntityArray.Add(str);
        }

        string createStringRefLabel(int index)
        {
            return "__string_ref_label_" + index;
        }

        byte[] bytes(byte[] aBytes)
        {
            if (machineEndian != option.OutputEndian)
            {
                Array.Reverse(aBytes);
            }
            return aBytes;
        }

        byte[] strSInt16ToBytes(string aStr)
        {
            return bytes(BitConverter.GetBytes(strToSInt16(aStr)));
        }

        byte[] strSInt32ToBytes(string aStr)
        {
            return bytes(BitConverter.GetBytes(strToSInt32(aStr)));
        }

        byte[] strSInt64ToBytes(string aStr)
        {
            return bytes(BitConverter.GetBytes(strToSInt64(aStr)));
        }

        byte[] strUInt16ToBytes(string aStr)
        {
            return bytes(BitConverter.GetBytes(strToUInt16(aStr)));
        }

        byte[] strUInt32ToBytes(string aStr)
        {
            return bytes(BitConverter.GetBytes(strToUInt32(aStr)));
        }

        byte[] strUInt64ToBytes(string aStr)
        {
            return bytes(BitConverter.GetBytes(strToUInt64(aStr)));
        }

        byte[] strFloat32ToBytes(string aStr)
        {
            return bytes(BitConverter.GetBytes(strToFloat32(aStr)));
        }

        byte[] strFloat64ToBytes(string aStr)
        {
            return bytes(BitConverter.GetBytes(strToFloat64(aStr)));
        }

        byte[] strToBytes(string aStr)
        {
            const UInt32 UINT32_SIZE = 4;
            byte[] allBytes = option.Encoding.GetBytes(aStr);
            byte[] destBytes = new byte[UINT32_SIZE + allBytes.Length + (option.Encoding.IsSingleByte ? 1 : 4)];
            Array.Copy(
                bytes(BitConverter.GetBytes((uint)(allBytes.Length)))
                , destBytes
                , UINT32_SIZE
                );
            Array.Copy(
                allBytes
                , 0
                , destBytes
                , UINT32_SIZE
                , allBytes.Length
                );
            for (int i = (int)UINT32_SIZE + allBytes.Length; i < destBytes.Length; ++i)
            {
                destBytes[i] = 0;
            }
            return destBytes;
        }

        static XmlAttribute checkAttributeExist(XmlAttributeCollection aAttrs, string aName)
        {
            XmlAttribute attr = aAttrs[aName];
            if (attr == null)
            {
                throw new Exception("Attribute named '" + aName + "' is not found.");
            }
            return attr;
        }

        static XmlAttribute checkAttributeEqual(XmlAttributeCollection aAttrs, string aName, string aValidValue)
        {
            XmlAttribute attr = checkAttributeExist(aAttrs, aName);
            if (attr.Value != aValidValue)
            {
                throw new Exception("Attribute named '" + aName + "' is not valid. This Value is '" + attr.Value + "'. Valid value is '" + aValidValue + "'.");
            }
            return attr;
        }

        static XmlAttribute checkAttributeLessEqual(XmlAttributeCollection aAttrs, string aName, Byte aValidValue)
        {
            XmlAttribute attr = checkAttributeExist(aAttrs, aName);
            Byte parsedValue = Byte.Parse(attr.Value);
            if (aValidValue < parsedValue)
            {
                throw new Exception("Attribute named '" + aName + "' is not valid. This Value is '" + attr.Value + "'. Valid value is less than '" + aValidValue + "'.");
            }
            return attr;
        }

        static SByte strToSInt8(string aStr)
        {
            SByte result;
            try
            {
                result = SByte.Parse(aStr);
            }
            catch (Exception)
            {
                throw new Exception("SInt8 parse error '" + aStr + "'.");
            }
            return result;
        }

        static Int16 strToSInt16(string aStr)
        {
            Int16 result;
            try
            {
                result = Int16.Parse(aStr);
            }
            catch (Exception)
            {
                throw new Exception("SInt16 parse error '" + aStr + "'.");
            }
            return result;
        }

        static Int32 strToSInt32(string aStr)
        {
            Int32 result;
            try
            {
                result = Int32.Parse(aStr);
            }
            catch (Exception)
            {
                throw new Exception("SInt32 parse error '" + aStr + "'.");
            }
            return result;
        }

        static Int64 strToSInt64(string aStr)
        {
            Int64 result;
            try
            {
                result = Int64.Parse(aStr);
            }
            catch (Exception)
            {
                throw new Exception("SInt64 parse error '" + aStr + "'.");
            }
            return result;
        }

        static Byte strToUInt8(string aStr)
        {
            Byte result;
            try
            {
                result = Byte.Parse(aStr);
            }
            catch (Exception)
            {
                throw new Exception("UInt8 parse error '" + aStr + "'.");
            }
            return result;
        }

        static UInt16 strToUInt16(string aStr)
        {
            UInt16 result;
            try
            {
                result = UInt16.Parse(aStr);
            }
            catch (Exception)
            {
                throw new Exception("UInt16 parse error '" + aStr + "'.");
            }
            return result;
        }

        static UInt32 strToUInt32(string aStr)
        {
            UInt32 result;
            try
            {
                result = UInt32.Parse(aStr);
            }
            catch (Exception)
            {
                throw new Exception("UInt32 parse error '" + aStr + "'.");
            }
            return result;
        }

        static UInt64 strToUInt64(string aStr)
        {
            UInt64 result;
            try
            {
                result = UInt64.Parse(aStr);
            }
            catch (Exception)
            {
                throw new Exception("UInt64 parse error '" + aStr + "'.");
            }
            return result;
        }

        static float strToFloat32(string aStr)
        {
            float result;
            try
            {
                result = float.Parse(aStr);
            }
            catch (Exception)
            {
                throw new Exception("Float32 parse error '" + aStr + "'.");
            }
            return result;
        }

        static double strToFloat64(string aStr)
        {
            double result;
            try
            {
                result = double.Parse(aStr);
            }
            catch (Exception)
            {
                throw new Exception("Float64 parse error '" + aStr + "'.");
            }
            return result;
        }

        static string nodeValue(XmlNode aNode)
        {
            return checkAttributeExist(aNode.Attributes, "value").Value;
        }

        static string[] arrayToStringArray(XmlNode aNode)
        {
            UInt32 arrayCount = strToUInt32(checkAttributeExist(aNode.Attributes, "count").Value);
            ArrayList list = new ArrayList();
            string innerText = aNode.InnerText;
            //innerText = innerText.Replace('\r', ' '); // ���s�����͔��p�X�y�[�X�ɒu�������B
            //innerText = innerText.Replace('\n', ' '); // ���s�����͔��p�X�y�[�X�ɒu�������B
            foreach (string str in innerText.Split(ARRAY_SPLIT_CHARS))
            {
                if (0 < str.Length)
                {
                    list.Add(str);
                }
            }
            string[] result = (string[])list.ToArray(typeof(string));
            if (result.Length != arrayCount)
            {
                throw new Exception("Array node named '" + aNode.Name + "' is not count '" + arrayCount + "' truly '" + result.Length + "'.");
            }
            return result;
        }
    }
}
