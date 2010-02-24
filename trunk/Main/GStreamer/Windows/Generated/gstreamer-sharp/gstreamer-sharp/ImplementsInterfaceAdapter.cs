// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst {

	using System;
	using System.Runtime.InteropServices;

#region Autogenerated code
	public partial class ImplementsInterfaceAdapter : Gst.GLib.GInterfaceAdapter, Gst.ImplementsInterface {

		[StructLayout (LayoutKind.Sequential)]
		struct GstImplementsInterfaceClass {
			public SupportedNativeDelegate Supported;
			[MarshalAs (UnmanagedType.ByValArray, SizeConst=4)]
			public IntPtr[] GstReserved;
		}

		static GstImplementsInterfaceClass iface;

		static ImplementsInterfaceAdapter ()
		{
			Gst.GLib.GType.Register (_gtype, typeof(ImplementsInterfaceAdapter));
			iface.Supported = new SupportedNativeDelegate (Supported_cb);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool SupportedNativeDelegate (IntPtr inst, IntPtr iface_type);

		static bool Supported_cb (IntPtr inst, IntPtr iface_type)
		{
			try {
				ImplementsInterfaceImplementor __obj = Gst.GLib.Object.GetObject (inst, false) as ImplementsInterfaceImplementor;
				bool __result = __obj.Supported (new Gst.GLib.GType(iface_type));
				return __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		static int class_offset = 2 * IntPtr.Size;

		static void Initialize (IntPtr ptr, IntPtr data)
		{
			IntPtr ifaceptr = new IntPtr (ptr.ToInt64 () + class_offset);
			GstImplementsInterfaceClass native_iface = (GstImplementsInterfaceClass) Marshal.PtrToStructure (ifaceptr, typeof (GstImplementsInterfaceClass));
			native_iface.Supported = iface.Supported;
			Marshal.StructureToPtr (native_iface, ifaceptr, false);
			GCHandle gch = (GCHandle) data;
			gch.Free ();
		}

		Gst.GLib.Object implementor;

		public ImplementsInterfaceAdapter ()
		{
			InitHandler = new Gst.GLib.GInterfaceInitHandler (Initialize);
		}

		public ImplementsInterfaceAdapter (ImplementsInterfaceImplementor implementor)
		{
			if (implementor == null)
				throw new ArgumentNullException ("implementor");
			else if (!(implementor is Gst.GLib.Object))
				throw new ArgumentException ("implementor must be a subclass of Gst.GLib.Object");
			this.implementor = implementor as Gst.GLib.Object;
		}

		public ImplementsInterfaceAdapter (IntPtr handle)
		{
			if (!_gtype.IsInstance (handle))
				throw new ArgumentException ("The gobject doesn't implement the GInterface of this adapter", "handle");
			implementor = Gst.GLib.Object.GetObject (handle);
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_implements_interface_get_type();

		private static Gst.GLib.GType _gtype = new Gst.GLib.GType (gst_implements_interface_get_type ());

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

		public static ImplementsInterface GetObject (IntPtr handle, bool owned)
		{
			Gst.GLib.Object obj = Gst.GLib.Object.GetObject (handle, owned);
			return GetObject (obj);
		}

		public static ImplementsInterface GetObject (Gst.GLib.Object obj)
		{
			if (obj == null)
				return null;
			else if (obj is ImplementsInterfaceImplementor)
				return new ImplementsInterfaceAdapter (obj as ImplementsInterfaceImplementor);
			else if (obj as ImplementsInterface == null)
				return new ImplementsInterfaceAdapter (obj.Handle);
			else
				return obj as ImplementsInterface;
		}

		public ImplementsInterfaceImplementor Implementor {
			get {
				return implementor as ImplementsInterfaceImplementor;
			}
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern bool gst_element_implements_interface(IntPtr raw, IntPtr iface_type);

		public bool Supported(Gst.GLib.GType iface_type) {
			bool raw_ret = gst_element_implements_interface(Handle, iface_type.Val);
			bool ret = raw_ret;
			return ret;
		}

#endregion
	}
}