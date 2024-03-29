﻿using System;
using System.IO;
using System.Collections.Generic;

namespace PlaylistMaker
{
    class BeBinaryReader : BinaryReader
    {
        public BeBinaryReader(Stream input) : base(input)
        {

        }
        public override short ReadInt16()
        {
            byte[] b = ReadBytes(2);
            return (short)(b[1] + (b[0] << 8));
        }
        public override int ReadInt32()
        {
            byte[] b = ReadBytes(4);
            if (b.Length == 4)
                return (b[3] + (b[2] << 8) + (b[1] << 16) + (b[0] << 24));
            else
                return -1;
        }
        public override ushort ReadUInt16()
        {
            byte[] b = ReadBytes(2);
            if (b.Length == 2)
                return (ushort)(b[1] + (b[0] << 8));
            else
                return 0;
        }
        public override uint ReadUInt32()
        {
            byte[] b = ReadBytes(4);
            if (b.Length == 4)
                return (uint)(b[3] + (b[2] << 8) + (b[1] << 16) + (b[0] << 24));
            else
                return 0;
        }
        public List<short> ReadMultipleShort(int count)
        {
            var list = new List<short>();
            for (var i = 0; i < count; i++)
                list.Add(this.ReadInt16());
            return list;
        }

    }
}
