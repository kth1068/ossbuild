// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst {

	using System;

	public delegate void PluginAddedHandler(object o, PluginAddedArgs args);

	public class PluginAddedArgs : Gst.GLib.SignalArgs {
		public Gst.Plugin Plugin{
			get {
				return (Gst.Plugin) Args [0];
			}
		}

	}
}