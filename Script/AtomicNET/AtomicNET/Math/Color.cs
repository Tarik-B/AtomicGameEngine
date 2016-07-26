using System.Runtime.InteropServices;

namespace AtomicEngine
{


    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct Color
    {
        public Color(float r, float g, float b, float a = 1.0f)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }

        // 0xffe6d8ad

        public static readonly Color White = new Color(1, 1, 1, 1);
        public static readonly Color LightBlue = new Color(0.50f, 0.88f, 0.81f);
        public static readonly Color Transparent = new Color(0, 0, 0, 0);

        public static Color operator *(Color value, float scale)
        {
            return new Color((int)(value.R * scale), (int)(value.G * scale), (int)(value.B * scale), (int)(value.A * scale));
        }

        public static Color Lerp(Color value1, Color value2, float amount)
        {
            amount = MathHelper.Clamp(amount, 0, 1);
            return new Color(
                (int)MathHelper.Lerp(value1.R, value2.R, amount),
                (int)MathHelper.Lerp(value1.G, value2.G, amount),
                (int)MathHelper.Lerp(value1.B, value2.B, amount),
                (int)MathHelper.Lerp(value1.A, value2.A, amount));
        }


        public float R;
        public float G;
        public float B;
        public float A;

    }
}