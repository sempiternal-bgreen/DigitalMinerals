using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Sapphire
{
    public partial class GraphicsPanel : Panel
    {
        public GraphicsPanel()
        {
            InitializeComponent();
            this.DoubleBuffered = true;
        }

        public GraphicsPanel(IContainer container)
        {
            container.Add(this);
            InitializeComponent();
        }
    }
}
