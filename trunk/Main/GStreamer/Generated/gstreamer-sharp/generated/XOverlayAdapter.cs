// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst.Interfaces {

	using System;
	using System.Runtime.InteropServices;

#region Autogenerated code
	public partial class XOverlayAdapter : Gst.GLib.GInterfaceAdapter, Gst.Interfaces.XOverlay {

		[StructLayout (LayoutKind.Sequential)]
		struct GstXOverlayClass {
			public SetXwindowIdNativeDelegate SetXwindowId;
			public ExposeNativeDelegate Expose;
			public HandleEventsNativeDelegate HandleEvents;
			[MarshalAs (UnmanagedType.ByValArray, SizeConst=3)]
			public IntPtr[] GstReserved;
		}

		static GstXOverlayClass iface;

		static XOverlayAdapter ()
		{
			Gst.GLib.GType.Register (_gtype, typeof(XOverlayAdapter));
			iface.SetXwindowId = new SetXwindowIdNativeDelegate (SetXwindowId_cb);
			iface.Expose = new ExposeNativeDelegate (Expose_cb);
			iface.HandleEvents = new HandleEventsNativeDelegate (HandleEvents_cb);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void SetXwindowIdNativeDelegate (IntPtr inst, UIntPtr xwindow_id);

		static void SetXwindowId_cb (IntPtr inst, UIntPtr xwindow_id)
		{
			try {
				XOverlayImplementor __obj = Gst.GLib.Object.GetObject (inst, false) as XOverlayImplementor;
				__obj.XwindowId = (ulong) xwindow_id;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void ExposeNativeDelegate (IntPtr inst);

		static void Expose_cb (IntPtr inst)
		{
			try {
				XOverlayImplementor __obj = Gst.GLib.Object.GetObject (inst, false) as XOverlayImplementor;
				__obj.Expose ();
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void HandleEventsNativeDelegate (IntPtr inst, bool handle_events);

		static void HandleEvents_cb (IntPtr inst, bool handle_events)
		{
			try {
				XOverlayImplementor __obj = Gst.GLib.Object.GetObject (inst, false) as XOverlayImplementor;
				__obj.HandleEvents (handle_events);
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		static int class_offset = 2 * IntPtr.Size;

		static void Initialize (IntPtr ptr, IntPtr data)
		{
			IntPtr ifaceptr = new IntPtr (ptr.ToInt64 () + class_offset);
			GstXOverlayClass native_iface = (GstXOverlayClass) Marshal.PtrToStructure (ifaceptr, typeof (GstXOverlayClass));
			native_iface.SetXwindowId = iface.SetXwindowId;
			native_iface.Expose = iface.Expose;
			native_iface.HandleEvents = iface.HandleEvents;
			Marshal.StructureToPtr (native_iface, ifaceptr, false);
			GCHandle gch = (GCHandle) data;
			gch.Free ();
		}

		Gst.GLib.Object implementor;

		public XOverlayAdapter ()
		{
			InitHandler = new Gst.GLib.GInterfaceInitHandler (Initialize);
		}

		public XOverlayAdapter (XOverlayImplementor implementor)
		{
			if (implementor == null)
				throw new ArgumentNullException ("implementor");
			else if (!(implementor is Gst.GLib.Object))
				throw new ArgumentException ("implementor must be a subclass of Gst.GLib.Object");
			this.implementor = implementor as Gst.GLib.Object;
		}

		public XOverlayAdapter (IntPtr handle)
		{
			if (!_gtype.IsInstance (handle))
				throw new ArgumentException ("The gobject doesn't implement the GInterface of this adapter", "handle");
			implementor = Gst.GLib.Object.GetObject (handle);
		}

		[DllImport("libgstinterfaces-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_x_overlay_get_type();

		private static Gst.GLib.GType _gtype = new Gst.GLib.GType (gst_x_overlay_get_type ());

		public override Gst.GLib.GType GType {
			get {
				return _gtype;
			}
		}

		public override IntPtr Handle {
			get {
				return implementor.Handle;
			}
		}

		public IntPtr OwnedHandle {
			get {
				return implementor.OwnedHandle;
			}
		}

		public static XOverlay GetObject (IntPtr handle, bool owned)
		{
			Gst.GLib.Object obj = Gst.GLib.Object.GetObject (handle, owned);
			return GetObject (obj);
		}

		public static XOverlay GetObject (Gst.GLib.Object obj)
		{
			if (obj == null)
				return null;
			else if (obj is XOverlayImplementor)
				return new XOverlayAdapter (obj as XOverlayImplementor);
			else if (obj as XOverlay == null)
				return new XOverlayAdapter (obj.Handle);
			else
				return obj as XOverlay;
		}

		public XOverlayImplementor Implementor {
			get {
				return implementor as XOverlayImplementor;
			}
		}

		[DllImport("libgstinterfaces-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_x_overlay_expose(IntPtr raw);

		public void Expose() {
			gst_x_overlay_expose(Handle);
		}

		[DllImport("libgstinterfaces-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_x_overlay_handle_events(IntPtr raw, bool handle_events);

		public void HandleEvents(bool handle_events) {
			gst_x_overlay_handle_events(Handle, handle_events);
		}

		[DllImport("libgstinterfaces-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_x_overlay_got_xwindow_id(IntPtr raw, UIntPtr xwindow_id);

		public void GotXwindowId(ulong xwindow_id) {
			gst_x_overlay_got_xwindow_id(Handle, new UIntPtr (xwindow_id));
		}

		[DllImport("libgstinterfaces-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_x_overlay_prepare_xwindow_id(IntPtr raw);

		public void PrepareXwindowId() {
			gst_x_overlay_prepare_xwindow_id(Handle);
		}

		[DllImport("libgstinterfaces-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_x_overlay_set_xwindow_id(IntPtr raw, UIntPtr xwindow_id);

		public ulong XwindowId { 
			set {
				gst_x_overlay_set_xwindow_id(Handle, new UIntPtr (value));
			}
		}

#endregion
	}
}