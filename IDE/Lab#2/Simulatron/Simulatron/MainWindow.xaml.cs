using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Media;
using NAudio.Wave;

namespace Simulatron
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private DispatcherTimer timer;
        public MainWindow()
        {
           


            this.timer = new DispatcherTimer();
            this.timer.Tick += timer_Tick;
            this.timer.Interval = new System.TimeSpan(0, 0, 1);
            this.timer.Start();

            InitializeComponent();
        }
        
        private void timer_Tick(object sender, System.EventArgs e)
        {
            this.progBar1.Value = System.DateTime.Now.Second;
            this.progBar2.Value = System.DateTime.Now.Second;
            this.progBar3.Value = System.DateTime.Now.Second;
            this.progBar4.Value = System.DateTime.Now.Second;
            this.progBar5.Value = System.DateTime.Now.Second;

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.timer = new DispatcherTimer();
            this.timer.Tick += timer_Tick;
            this.timer.Interval = new System.TimeSpan(0, 0, 1);
            this.timer.Start();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            SoundPlayer simpleSound = new SoundPlayer(@"E:\Documents\University\Year II\Labs\IDE\Lab#2\Simulatron\Simulatron\Resources\imperial.wav");

            //Play Sound On Click
            simpleSound.Play();
        }
        
        
    }

}
