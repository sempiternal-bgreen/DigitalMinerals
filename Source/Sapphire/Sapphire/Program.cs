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
        public static extern bool _InitializeD3D(Int32 handle, float screenWidth, float screenHeight);

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

        [DllImport("Onyx")]
        public static extern void _PostProcessMaximizeThresholdColors();

        [STAThread]
        static void Main()
        {
            // Create Our Own Form
            SapphireForm Form = new SapphireForm();

            // Show Everthing On the Form
            Form.Show();

            // Send Our Handle To D3D Engine Side
            _InitializeD3D( Form.graphicsPanel1.Handle.ToInt32(), Form.graphicsPanel1.Width, Form.graphicsPanel1.Height );

            // Set Our Post Process Combo Box to "No Effect"
            Form.PostProcessComboBox.SelectedIndex = 0;

            // Loop While We Have a Form
            while (Form.Created)
            {
                // Do All The Events Within The Application
                Application.DoEvents();

                // Update our Engine
                _UpdateD3D();

                // Render our Engine
                _RenderD3D();

                // Display FrameRate Onto the Form Using our GetFPS() Function 
                Form.FramesPerSecond.Text = Convert.ToString(_GetFPS());
            }
        }
    }
}
