using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Sapphire
{
    public partial class SapphireForm : Form
    {
        public Point initialMouse;
        public bool toggleCamera = false;
        public SapphireForm()
        {
            InitializeComponent();

        }

        private void SapphireFileExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void PostProcessCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            Program._TogglePostProcess(PostProcessCheckBox.Checked);
        }

        private void PostProcessComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            Program._SetPostProcessEffect(PostProcessComboBox.SelectedIndex);

            if (PostProcessComboBox.SelectedIndex == 10)
            {
                Program._PostProcessMaximizeThresholdColors();
            }
        }

        private void SapphireForm_Load(object sender, EventArgs e)
        {

        }

        private void graphicsPanel1_MouseEnter(object sender, EventArgs e)
        {
            graphicsPanel1.Focus();
            graphicsPanel3.BackColor = Color.MediumSlateBlue;
        }

        private void graphicsPanel1_MouseDown(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Right:
                    {
                        // Set initial point for mouse move
                        toggleCamera = !toggleCamera;
                        Program._SetCameraToggle(toggleCamera);
                        initialMouse = e.Location;
                        if (toggleCamera)
                        {
                            graphicsPanel3.BackColor = Color.Red;
                        }
                        else
                        {
                            graphicsPanel3.BackColor = SystemColors.ControlLight;
                        }
                        break;
                    }
            }
        }

        private void graphicsPanel1_MouseLeave(object sender, EventArgs e)
        {
            graphicsPanel3.BackColor = SystemColors.ControlLight;
            Program._SetCameraToggle(false);
        }

        private void graphicsPanel1_MouseClick(object sender, MouseEventArgs e)
        {

        }

        private void VSyncCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            Program._ToggleVSync(VSyncCheckBox.Checked);
            graphicsPanel1.Invalidate();
        }

    }
}
