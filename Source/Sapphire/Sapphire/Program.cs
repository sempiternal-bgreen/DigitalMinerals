using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing;

namespace Sapphire
{
    static class Program
    {
        [DllImport("Onyx")]
        public static extern bool _InitializeD3D(Int32 handle);

        [DllImport("Onyx")]
        public static extern void _RenderD3D();

        [DllImport("Onyx")]
        public static extern void _UpdateD3D();

        [DllImport("Onyx")]
        public static extern int _GetFPS();

        [DllImport("Onyx")]
        public static extern void _ToggleVSync(bool set);

        [DllImport("Onyx")]
        public static extern void _ShutDownD3D();

        [DllImport("Onyx")]
        public static extern void _ResetD3D();

        [DllImport("Onyx")]
        public static extern void _TogglePostProcess(bool set);

        [DllImport("Onyx")]
        public static extern void _SetPostProcessEffect( int set );

        [STAThread]
        static void Main()
        {
            SapphireForm Form = new SapphireForm();
            Form.Show();

            _InitializeD3D( Form.graphicsPanel1.Handle.ToInt32() );

            while (Form.Created)
            {
                Application.DoEvents();
                _UpdateD3D();
                _RenderD3D();
                Form.FramesPerSecond.Text = Convert.ToString(_GetFPS());
            }
        }
    }
}
