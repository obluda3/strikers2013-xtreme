using System;
using System.Text;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace PlaylistMaker
{
    class Program
    {
        static void Main(string[] args)
        {
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);
            string path;
            if (args.Length < 1)
            {
                Console.WriteLine("Drag a txt file onto the window");
                path = Console.ReadLine();
            }
            else path = args[0];

            var bgmNames = File.ReadAllLines(path).ToList();
            var openingFirst = bgmNames.IndexOf("###OPENINGS###");
            if (openingFirst >= 0) bgmNames.RemoveAt(openingFirst);
            var bgmData = bgmNames.Select(x => StringToCString(x));

            var directory = Path.GetDirectoryName(path);
            var output = File.OpenWrite(directory + "\\Playlist.bin");

            using (var bw = new BeBinaryWriter(output))
            {
                var magic = new byte[] { 0x50, 0x4c, 0x56, 0x31 };
                bw.Write(magic);
                bw.Write(bgmNames.Count);
                bw.Write(openingFirst);
                for (var i = 0; i < bgmNames.Count; i++) bw.Write(0);

                List<int> pointers = new();
                bgmData.ToList().ForEach(x => 
                {   pointers.Add((int)bw.BaseStream.Position);
                    bw.Write(x);
                });
                bw.BaseStream.Position = 12;
                pointers.ForEach(x => bw.Write(x));
            }
            Console.WriteLine("Done.");
            Console.Read();
        }

        static byte[] StringToCString(string input)
        {
            var encoded = Encoding.GetEncoding("shift_jis").GetBytes(input);

            var padded = ((encoded.Length / 4) + 1) * 4;
            var output = new byte[padded];
            Array.Copy(encoded, output, encoded.Length);

            for (var i = encoded.Length; i < padded; i++) output[i] = 0;
            return output;
        }
    }
}
