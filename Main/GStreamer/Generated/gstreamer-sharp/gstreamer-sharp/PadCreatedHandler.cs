// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst {

	using System;

	public delegate void PadCreatedHandler(object o, PadCreatedArgs args);

	public class PadCreatedArgs : Gst.GLib.SignalArgs {
		public Gst.Pad Pad{
			get {
				return (Gst.Pad) Args [0];
			}
		}

	}
}