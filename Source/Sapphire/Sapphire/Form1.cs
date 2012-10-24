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

        private void PostProcessTab_MouseDown(object sender, MouseEventArgs e)
        {
            
        }
    }
}
