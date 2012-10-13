namespace Sapphire
{
    partial class SapphireForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.graphicsPanel1 = new Sapphire.GraphicsPanel(this.components);
            this.SapphireMenu = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.graphicsPanel2 = new Sapphire.GraphicsPanel(this.components);
            this.SapphireMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // graphicsPanel1
            // 
            this.graphicsPanel1.BackColor = System.Drawing.Color.Black;
            this.graphicsPanel1.Location = new System.Drawing.Point(12, 37);
            this.graphicsPanel1.Name = "graphicsPanel1";
            this.graphicsPanel1.Size = new System.Drawing.Size(640, 480);
            this.graphicsPanel1.TabIndex = 0;
            // 
            // SapphireMenu
            // 
            this.SapphireMenu.BackColor = System.Drawing.Color.DarkSlateGray;
            this.SapphireMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.optionsToolStripMenuItem});
            this.SapphireMenu.Location = new System.Drawing.Point(0, 0);
            this.SapphireMenu.Name = "SapphireMenu";
            this.SapphireMenu.Size = new System.Drawing.Size(1015, 24);
            this.SapphireMenu.TabIndex = 1;
            this.SapphireMenu.Text = "Menu";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.optionsToolStripMenuItem.Text = "Options";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            // 
            // graphicsPanel2
            // 
            this.graphicsPanel2.BackColor = System.Drawing.Color.DarkSlateGray;
            this.graphicsPanel2.Location = new System.Drawing.Point(0, 531);
            this.graphicsPanel2.Name = "graphicsPanel2";
            this.graphicsPanel2.Size = new System.Drawing.Size(1015, 24);
            this.graphicsPanel2.TabIndex = 2;
            // 
            // SapphireForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1015, 567);
            this.Controls.Add(this.graphicsPanel2);
            this.Controls.Add(this.graphicsPanel1);
            this.Controls.Add(this.SapphireMenu);
            this.MainMenuStrip = this.SapphireMenu;
            this.Name = "SapphireForm";
            this.Text = "Sapphire";
            this.SapphireMenu.ResumeLayout(false);
            this.SapphireMenu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public GraphicsPanel graphicsPanel1;
        private System.Windows.Forms.MenuStrip SapphireMenu;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private GraphicsPanel graphicsPanel2;

    }
}

