// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst.Base {

	using System;
	using System.Collections;
	using System.Runtime.InteropServices;

#region Autogenerated code
	public partial class BaseTransform : Gst.Element {

		public BaseTransform(IntPtr raw) : base(raw) {}

		protected BaseTransform() : base(IntPtr.Zero)
		{
			CreateNativeObject (new string [0], new Gst.GLib.Value [0]);
		}

		[Gst.GLib.Property ("qos")]
		public bool Qos {
			get {
				Gst.GLib.Value val = GetProperty ("qos");
				bool ret = (bool) val;
				val.Dispose ();
				return ret;
			}
			set {
				Gst.GLib.Value val = new Gst.GLib.Value(value);
				SetProperty("qos", val);
				val.Dispose ();
			}
		}

		[DllImport("libgstbase-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern bool gst_base_transform_is_passthrough(IntPtr raw);

		[DllImport("libgstbase-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_base_transform_set_passthrough(IntPtr raw, bool passthrough);

		public bool Passthrough {
			get  {
				bool raw_ret = gst_base_transform_is_passthrough(Handle);
				bool ret = raw_ret;
				return ret;
			}
			set  {
				gst_base_transform_set_passthrough(Handle, value);
			}
		}

		static TransformCapsNativeDelegate TransformCaps_cb_delegate;
		static TransformCapsNativeDelegate TransformCapsVMCallback {
			get {
				if (TransformCaps_cb_delegate == null)
					TransformCaps_cb_delegate = new TransformCapsNativeDelegate (TransformCaps_cb);
				return TransformCaps_cb_delegate;
			}
		}

		static void OverrideTransformCaps (Gst.GLib.GType gtype)
		{
			OverrideTransformCaps (gtype, TransformCapsVMCallback);
		}

		static void OverrideTransformCaps (Gst.GLib.GType gtype, TransformCapsNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.TransformCaps = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate IntPtr TransformCapsNativeDelegate (IntPtr inst, int direction, IntPtr caps);

		static IntPtr TransformCaps_cb (IntPtr inst, int direction, IntPtr caps)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				Gst.Caps __result = __obj.OnTransformCaps ((Gst.PadDirection) direction, caps == IntPtr.Zero ? null : (Gst.Caps) Gst.GLib.Opaque.GetOpaque (caps, typeof (Gst.Caps), false));
				return __result == null ? IntPtr.Zero : __result.OwnedCopy;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideTransformCaps")]
		protected virtual Gst.Caps OnTransformCaps (Gst.PadDirection direction, Gst.Caps caps)
		{
			return InternalTransformCaps (direction, caps);
		}

		private Gst.Caps InternalTransformCaps (Gst.PadDirection direction, Gst.Caps caps)
		{
			TransformCapsNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).TransformCaps;
			if (unmanaged == null) return null;

			IntPtr __result = unmanaged (this.Handle, (int) direction, caps == null ? IntPtr.Zero : caps.Handle);
			return __result == IntPtr.Zero ? null : (Gst.Caps) Gst.GLib.Opaque.GetOpaque (__result, typeof (Gst.Caps), true);
		}

		static FixateCapsNativeDelegate FixateCaps_cb_delegate;
		static FixateCapsNativeDelegate FixateCapsVMCallback {
			get {
				if (FixateCaps_cb_delegate == null)
					FixateCaps_cb_delegate = new FixateCapsNativeDelegate (FixateCaps_cb);
				return FixateCaps_cb_delegate;
			}
		}

		static void OverrideFixateCaps (Gst.GLib.GType gtype)
		{
			OverrideFixateCaps (gtype, FixateCapsVMCallback);
		}

		static void OverrideFixateCaps (Gst.GLib.GType gtype, FixateCapsNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.FixateCaps = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void FixateCapsNativeDelegate (IntPtr inst, int direction, IntPtr caps, IntPtr othercaps);

		static void FixateCaps_cb (IntPtr inst, int direction, IntPtr caps, IntPtr othercaps)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				__obj.OnFixateCaps ((Gst.PadDirection) direction, caps == IntPtr.Zero ? null : (Gst.Caps) Gst.GLib.Opaque.GetOpaque (caps, typeof (Gst.Caps), false), othercaps == IntPtr.Zero ? null : (Gst.Caps) Gst.GLib.Opaque.GetOpaque (othercaps, typeof (Gst.Caps), false));
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideFixateCaps")]
		protected virtual void OnFixateCaps (Gst.PadDirection direction, Gst.Caps caps, Gst.Caps othercaps)
		{
			InternalFixateCaps (direction, caps, othercaps);
		}

		private void InternalFixateCaps (Gst.PadDirection direction, Gst.Caps caps, Gst.Caps othercaps)
		{
			FixateCapsNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).FixateCaps;
			if (unmanaged == null) return;

			unmanaged (this.Handle, (int) direction, caps == null ? IntPtr.Zero : caps.Handle, othercaps == null ? IntPtr.Zero : othercaps.Handle);
		}

		static TransformSizeNativeDelegate TransformSize_cb_delegate;
		static TransformSizeNativeDelegate TransformSizeVMCallback {
			get {
				if (TransformSize_cb_delegate == null)
					TransformSize_cb_delegate = new TransformSizeNativeDelegate (TransformSize_cb);
				return TransformSize_cb_delegate;
			}
		}

		static void OverrideTransformSize (Gst.GLib.GType gtype)
		{
			OverrideTransformSize (gtype, TransformSizeVMCallback);
		}

		static void OverrideTransformSize (Gst.GLib.GType gtype, TransformSizeNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.TransformSize = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool TransformSizeNativeDelegate (IntPtr inst, int direction, IntPtr caps, uint size, IntPtr othercaps, out uint othersize);

		static bool TransformSize_cb (IntPtr inst, int direction, IntPtr caps, uint size, IntPtr othercaps, out uint othersize)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				bool __result = __obj.OnTransformSize ((Gst.PadDirection) direction, caps == IntPtr.Zero ? null : (Gst.Caps) Gst.GLib.Opaque.GetOpaque (caps, typeof (Gst.Caps), false), size, othercaps == IntPtr.Zero ? null : (Gst.Caps) Gst.GLib.Opaque.GetOpaque (othercaps, typeof (Gst.Caps), false), out othersize);
				return __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideTransformSize")]
		protected virtual bool OnTransformSize (Gst.PadDirection direction, Gst.Caps caps, uint size, Gst.Caps othercaps, out uint othersize)
		{
			return InternalTransformSize (direction, caps, size, othercaps, out othersize);
		}

		private bool InternalTransformSize (Gst.PadDirection direction, Gst.Caps caps, uint size, Gst.Caps othercaps, out uint othersize)
		{
			TransformSizeNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).TransformSize;
			if (unmanaged == null) throw new InvalidOperationException ("No base method to invoke");

			bool __result = unmanaged (this.Handle, (int) direction, caps == null ? IntPtr.Zero : caps.Handle, size, othercaps == null ? IntPtr.Zero : othercaps.Handle, out othersize);
			return __result;
		}

		static GetUnitSizeNativeDelegate GetUnitSize_cb_delegate;
		static GetUnitSizeNativeDelegate GetUnitSizeVMCallback {
			get {
				if (GetUnitSize_cb_delegate == null)
					GetUnitSize_cb_delegate = new GetUnitSizeNativeDelegate (GetUnitSize_cb);
				return GetUnitSize_cb_delegate;
			}
		}

		static void OverrideGetUnitSize (Gst.GLib.GType gtype)
		{
			OverrideGetUnitSize (gtype, GetUnitSizeVMCallback);
		}

		static void OverrideGetUnitSize (Gst.GLib.GType gtype, GetUnitSizeNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.GetUnitSize = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool GetUnitSizeNativeDelegate (IntPtr inst, IntPtr caps, out uint size);

		static bool GetUnitSize_cb (IntPtr inst, IntPtr caps, out uint size)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				bool __result = __obj.OnGetUnitSize (caps == IntPtr.Zero ? null : (Gst.Caps) Gst.GLib.Opaque.GetOpaque (caps, typeof (Gst.Caps), false), out size);
				return __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideGetUnitSize")]
		protected virtual bool OnGetUnitSize (Gst.Caps caps, out uint size)
		{
			return InternalGetUnitSize (caps, out size);
		}

		private bool InternalGetUnitSize (Gst.Caps caps, out uint size)
		{
			GetUnitSizeNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).GetUnitSize;
			if (unmanaged == null) throw new InvalidOperationException ("No base method to invoke");

			bool __result = unmanaged (this.Handle, caps == null ? IntPtr.Zero : caps.Handle, out size);
			return __result;
		}

		static SetCapsNativeDelegate SetCaps_cb_delegate;
		static SetCapsNativeDelegate SetCapsVMCallback {
			get {
				if (SetCaps_cb_delegate == null)
					SetCaps_cb_delegate = new SetCapsNativeDelegate (SetCaps_cb);
				return SetCaps_cb_delegate;
			}
		}

		static void OverrideSetCaps (Gst.GLib.GType gtype)
		{
			OverrideSetCaps (gtype, SetCapsVMCallback);
		}

		static void OverrideSetCaps (Gst.GLib.GType gtype, SetCapsNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.SetCaps = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool SetCapsNativeDelegate (IntPtr inst, IntPtr incaps, IntPtr outcaps);

		static bool SetCaps_cb (IntPtr inst, IntPtr incaps, IntPtr outcaps)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				bool __result = __obj.OnSetCaps (incaps == IntPtr.Zero ? null : (Gst.Caps) Gst.GLib.Opaque.GetOpaque (incaps, typeof (Gst.Caps), false), outcaps == IntPtr.Zero ? null : (Gst.Caps) Gst.GLib.Opaque.GetOpaque (outcaps, typeof (Gst.Caps), false));
				return __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideSetCaps")]
		protected virtual bool OnSetCaps (Gst.Caps incaps, Gst.Caps outcaps)
		{
			return InternalSetCaps (incaps, outcaps);
		}

		private bool InternalSetCaps (Gst.Caps incaps, Gst.Caps outcaps)
		{
			SetCapsNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).SetCaps;
			if (unmanaged == null) return true;

			bool __result = unmanaged (this.Handle, incaps == null ? IntPtr.Zero : incaps.Handle, outcaps == null ? IntPtr.Zero : outcaps.Handle);
			return __result;
		}

		static StartNativeDelegate Start_cb_delegate;
		static StartNativeDelegate StartVMCallback {
			get {
				if (Start_cb_delegate == null)
					Start_cb_delegate = new StartNativeDelegate (Start_cb);
				return Start_cb_delegate;
			}
		}

		static void OverrideStart (Gst.GLib.GType gtype)
		{
			OverrideStart (gtype, StartVMCallback);
		}

		static void OverrideStart (Gst.GLib.GType gtype, StartNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.Start = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool StartNativeDelegate (IntPtr inst);

		static bool Start_cb (IntPtr inst)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				bool __result = __obj.OnStart ();
				return __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideStart")]
		protected virtual bool OnStart ()
		{
			return InternalStart ();
		}

		private bool InternalStart ()
		{
			StartNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).Start;
			if (unmanaged == null) return false;

			bool __result = unmanaged (this.Handle);
			return __result;
		}

		static StopNativeDelegate Stop_cb_delegate;
		static StopNativeDelegate StopVMCallback {
			get {
				if (Stop_cb_delegate == null)
					Stop_cb_delegate = new StopNativeDelegate (Stop_cb);
				return Stop_cb_delegate;
			}
		}

		static void OverrideStop (Gst.GLib.GType gtype)
		{
			OverrideStop (gtype, StopVMCallback);
		}

		static void OverrideStop (Gst.GLib.GType gtype, StopNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.Stop = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool StopNativeDelegate (IntPtr inst);

		static bool Stop_cb (IntPtr inst)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				bool __result = __obj.OnStop ();
				return __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideStop")]
		protected virtual bool OnStop ()
		{
			return InternalStop ();
		}

		private bool InternalStop ()
		{
			StopNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).Stop;
			if (unmanaged == null) return false;

			bool __result = unmanaged (this.Handle);
			return __result;
		}

		static EventNativeDelegate Event_cb_delegate;
		static EventNativeDelegate EventVMCallback {
			get {
				if (Event_cb_delegate == null)
					Event_cb_delegate = new EventNativeDelegate (Event_cb);
				return Event_cb_delegate;
			}
		}

		static void OverrideEvent (Gst.GLib.GType gtype)
		{
			OverrideEvent (gtype, EventVMCallback);
		}

		static void OverrideEvent (Gst.GLib.GType gtype, EventNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.Event = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool EventNativeDelegate (IntPtr inst, IntPtr evnt);

		static bool Event_cb (IntPtr inst, IntPtr evnt)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				bool __result = __obj.OnEvent (Gst.MiniObject.GetObject(evnt) as Gst.Event);
				return __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideEvent")]
		protected virtual bool OnEvent (Gst.Event evnt)
		{
			return InternalEvent (evnt);
		}

		private bool InternalEvent (Gst.Event evnt)
		{
			EventNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).Event;
			if (unmanaged == null) return false;

			bool __result = unmanaged (this.Handle, evnt == null ? IntPtr.Zero : evnt.Handle);
			return __result;
		}

		static TransformNativeDelegate Transform_cb_delegate;
		static TransformNativeDelegate TransformVMCallback {
			get {
				if (Transform_cb_delegate == null)
					Transform_cb_delegate = new TransformNativeDelegate (Transform_cb);
				return Transform_cb_delegate;
			}
		}

		static void OverrideTransform (Gst.GLib.GType gtype)
		{
			OverrideTransform (gtype, TransformVMCallback);
		}

		static void OverrideTransform (Gst.GLib.GType gtype, TransformNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.Transform = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate int TransformNativeDelegate (IntPtr inst, IntPtr inbuf, IntPtr outbuf);

		static int Transform_cb (IntPtr inst, IntPtr inbuf, IntPtr outbuf)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				Gst.Buffer myoutbuf = Gst.MiniObject.GetObject(outbuf, true) as Gst.Buffer;
				Gst.FlowReturn __result = __obj.OnTransform (Gst.MiniObject.GetObject(inbuf) as Gst.Buffer, myoutbuf);
				IntPtr dummy = myoutbuf.OwnedHandle;
				myoutbuf.Dispose();
				return (int) __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideTransform")]
		protected virtual Gst.FlowReturn OnTransform (Gst.Buffer inbuf, Gst.Buffer outbuf)
		{
			return InternalTransform (inbuf, outbuf);
		}

		private Gst.FlowReturn InternalTransform (Gst.Buffer inbuf, Gst.Buffer outbuf)
		{
			TransformNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).Transform;
			if (unmanaged == null) return (Gst.FlowReturn) 0;

			int __result = unmanaged (this.Handle, inbuf == null ? IntPtr.Zero : inbuf.Handle, outbuf == null ? IntPtr.Zero : outbuf.Handle);
			return (Gst.FlowReturn) __result;
		}

		static TransformIpNativeDelegate TransformIp_cb_delegate;
		static TransformIpNativeDelegate TransformIpVMCallback {
			get {
				if (TransformIp_cb_delegate == null)
					TransformIp_cb_delegate = new TransformIpNativeDelegate (TransformIp_cb);
				return TransformIp_cb_delegate;
			}
		}

		static void OverrideTransformIp (Gst.GLib.GType gtype)
		{
			OverrideTransformIp (gtype, TransformIpVMCallback);
		}

		static void OverrideTransformIp (Gst.GLib.GType gtype, TransformIpNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.TransformIp = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate int TransformIpNativeDelegate (IntPtr inst, IntPtr buf);

		static int TransformIp_cb (IntPtr inst, IntPtr buf)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				Gst.Buffer mybuf = Gst.MiniObject.GetObject(buf, true) as Gst.Buffer;
				Gst.FlowReturn __result = __obj.OnTransformIp (mybuf);
				IntPtr dummy = mybuf.OwnedHandle;
				mybuf.Dispose();
				return (int) __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideTransformIp")]
		protected virtual Gst.FlowReturn OnTransformIp (Gst.Buffer buf)
		{
			return InternalTransformIp (buf);
		}

		private Gst.FlowReturn InternalTransformIp (Gst.Buffer buf)
		{
			TransformIpNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).TransformIp;
			if (unmanaged == null) return (Gst.FlowReturn) 0;

			int __result = unmanaged (this.Handle, buf == null ? IntPtr.Zero : buf.Handle);
			return (Gst.FlowReturn) __result;
		}

		static PrepareOutputBufferNativeDelegate PrepareOutputBuffer_cb_delegate;
		static PrepareOutputBufferNativeDelegate PrepareOutputBufferVMCallback {
			get {
				if (PrepareOutputBuffer_cb_delegate == null)
					PrepareOutputBuffer_cb_delegate = new PrepareOutputBufferNativeDelegate (PrepareOutputBuffer_cb);
				return PrepareOutputBuffer_cb_delegate;
			}
		}

		static void OverridePrepareOutputBuffer (Gst.GLib.GType gtype)
		{
			OverridePrepareOutputBuffer (gtype, PrepareOutputBufferVMCallback);
		}

		static void OverridePrepareOutputBuffer (Gst.GLib.GType gtype, PrepareOutputBufferNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.PrepareOutputBuffer = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate int PrepareOutputBufferNativeDelegate (IntPtr inst, IntPtr input, int size, IntPtr caps, out IntPtr buf);

		static int PrepareOutputBuffer_cb (IntPtr inst, IntPtr input, int size, IntPtr caps, out IntPtr buf)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				Gst.Buffer mybuf;
				Gst.FlowReturn __result = __obj.OnPrepareOutputBuffer (Gst.MiniObject.GetObject(input) as Gst.Buffer, size, caps == IntPtr.Zero ? null : (Gst.Caps) Gst.GLib.Opaque.GetOpaque (caps, typeof (Gst.Caps), false), out mybuf);
				buf = mybuf == null ? IntPtr.Zero : mybuf.Handle;
				return (int) __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverridePrepareOutputBuffer")]
		protected virtual Gst.FlowReturn OnPrepareOutputBuffer (Gst.Buffer input, int size, Gst.Caps caps, out Gst.Buffer buf)
		{
			return InternalPrepareOutputBuffer (input, size, caps, out buf);
		}

		private Gst.FlowReturn InternalPrepareOutputBuffer (Gst.Buffer input, int size, Gst.Caps caps, out Gst.Buffer buf)
		{
			PrepareOutputBufferNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).PrepareOutputBuffer;
			if (unmanaged == null) throw new InvalidOperationException ("No base method to invoke");

			IntPtr native_buf;
			int __result = unmanaged (this.Handle, input == null ? IntPtr.Zero : input.Handle, size, caps == null ? IntPtr.Zero : caps.Handle, out native_buf);
			buf = Gst.MiniObject.GetObject(native_buf, true) as Gst.Buffer;
			return (Gst.FlowReturn) __result;
		}

		static SrcEventNativeDelegate SrcEvent_cb_delegate;
		static SrcEventNativeDelegate SrcEventVMCallback {
			get {
				if (SrcEvent_cb_delegate == null)
					SrcEvent_cb_delegate = new SrcEventNativeDelegate (SrcEvent_cb);
				return SrcEvent_cb_delegate;
			}
		}

		static void OverrideSrcEvent (Gst.GLib.GType gtype)
		{
			OverrideSrcEvent (gtype, SrcEventVMCallback);
		}

		static void OverrideSrcEvent (Gst.GLib.GType gtype, SrcEventNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.SrcEvent = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool SrcEventNativeDelegate (IntPtr inst, IntPtr evnt);

		static bool SrcEvent_cb (IntPtr inst, IntPtr evnt)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				bool __result = __obj.OnSrcEvent (Gst.MiniObject.GetObject(evnt) as Gst.Event);
				return __result;
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideSrcEvent")]
		protected virtual bool OnSrcEvent (Gst.Event evnt)
		{
			return InternalSrcEvent (evnt);
		}

		private bool InternalSrcEvent (Gst.Event evnt)
		{
			SrcEventNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).SrcEvent;
			if (unmanaged == null) return false;

			bool __result = unmanaged (this.Handle, evnt == null ? IntPtr.Zero : evnt.Handle);
			return __result;
		}

		static BeforeTransformNativeDelegate BeforeTransform_cb_delegate;
		static BeforeTransformNativeDelegate BeforeTransformVMCallback {
			get {
				if (BeforeTransform_cb_delegate == null)
					BeforeTransform_cb_delegate = new BeforeTransformNativeDelegate (BeforeTransform_cb);
				return BeforeTransform_cb_delegate;
			}
		}

		static void OverrideBeforeTransform (Gst.GLib.GType gtype)
		{
			OverrideBeforeTransform (gtype, BeforeTransformVMCallback);
		}

		static void OverrideBeforeTransform (Gst.GLib.GType gtype, BeforeTransformNativeDelegate callback)
		{
			GstBaseTransformClass class_iface = GetClassStruct (gtype, false);
			class_iface.BeforeTransform = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void BeforeTransformNativeDelegate (IntPtr inst, IntPtr buffer);

		static void BeforeTransform_cb (IntPtr inst, IntPtr buffer)
		{
			try {
				BaseTransform __obj = Gst.GLib.Object.GetObject (inst, false) as BaseTransform;
				__obj.OnBeforeTransform (Gst.MiniObject.GetObject(buffer) as Gst.Buffer);
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Base.BaseTransform), ConnectionMethod="OverrideBeforeTransform")]
		protected virtual void OnBeforeTransform (Gst.Buffer buffer)
		{
			InternalBeforeTransform (buffer);
		}

		private void InternalBeforeTransform (Gst.Buffer buffer)
		{
			BeforeTransformNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).BeforeTransform;
			if (unmanaged == null) return;

			unmanaged (this.Handle, buffer == null ? IntPtr.Zero : buffer.Handle);
		}

		[StructLayout (LayoutKind.Sequential)]
		struct GstBaseTransformClass {
			public TransformCapsNativeDelegate TransformCaps;
			public FixateCapsNativeDelegate FixateCaps;
			public TransformSizeNativeDelegate TransformSize;
			public GetUnitSizeNativeDelegate GetUnitSize;
			public SetCapsNativeDelegate SetCaps;
			public StartNativeDelegate Start;
			public StopNativeDelegate Stop;
			public EventNativeDelegate Event;
			public TransformNativeDelegate Transform;
			public TransformIpNativeDelegate TransformIp;
			public bool PassthroughOnSameCaps;
			public PrepareOutputBufferNativeDelegate PrepareOutputBuffer;
			public SrcEventNativeDelegate SrcEvent;
			public BeforeTransformNativeDelegate BeforeTransform;
			[MarshalAs (UnmanagedType.ByValArray, SizeConst=18)]
			public IntPtr[] GstReserved;
		}

		static uint class_offset = ((Gst.GLib.GType) typeof (Gst.Element)).GetClassSize ();
		static Hashtable class_structs;

		static GstBaseTransformClass GetClassStruct (Gst.GLib.GType gtype, bool use_cache)
		{
			if (class_structs == null)
				class_structs = new Hashtable ();

			if (use_cache && class_structs.Contains (gtype))
				return (GstBaseTransformClass) class_structs [gtype];
			else {
				IntPtr class_ptr = new IntPtr (gtype.GetClassPtr ().ToInt64 () + class_offset);
				GstBaseTransformClass class_struct = (GstBaseTransformClass) Marshal.PtrToStructure (class_ptr, typeof (GstBaseTransformClass));
				if (use_cache)
					class_structs.Add (gtype, class_struct);
				return class_struct;
			}
		}

		static void OverrideClassStruct (Gst.GLib.GType gtype, GstBaseTransformClass class_struct)
		{
			IntPtr class_ptr = new IntPtr (gtype.GetClassPtr ().ToInt64 () + class_offset);
			Marshal.StructureToPtr (class_struct, class_ptr, false);
		}

		[DllImport("libgstbase-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_base_transform_reconfigure(IntPtr raw);

		public void Reconfigure() {
			gst_base_transform_reconfigure(Handle);
		}

		[DllImport("libgstbase-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_base_transform_suggest(IntPtr raw, IntPtr caps, uint size);

		public void Suggest(Gst.Caps caps, uint size) {
			gst_base_transform_suggest(Handle, caps == null ? IntPtr.Zero : caps.Handle, size);
		}

		[DllImport("libgstbase-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_base_transform_update_qos(IntPtr raw, double proportion, long diff, ulong timestamp);

		public void UpdateQos(double proportion, long diff, ulong timestamp) {
			gst_base_transform_update_qos(Handle, proportion, diff, timestamp);
		}

		[DllImport("libgstbase-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern bool gst_base_transform_is_in_place(IntPtr raw);

		[DllImport("libgstbase-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_base_transform_set_in_place(IntPtr raw, bool in_place);

		public bool InPlace { 
			get {
				bool raw_ret = gst_base_transform_is_in_place(Handle);
				bool ret = raw_ret;
				return ret;
			}
			set {
				gst_base_transform_set_in_place(Handle, value);
			}
		}

		[DllImport("libgstbase-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_base_transform_set_gap_aware(IntPtr raw, bool gap_aware);

		public bool GapAware { 
			set {
				gst_base_transform_set_gap_aware(Handle, value);
			}
		}

		[DllImport("libgstbase-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_base_transform_get_type();

		public static new Gst.GLib.GType GType { 
			get {
				IntPtr raw_ret = gst_base_transform_get_type();
				Gst.GLib.GType ret = new Gst.GLib.GType(raw_ret);
				return ret;
			}
		}


		static BaseTransform ()
		{
			GtkSharp.GstreamerSharp.ObjectManager.Initialize ();
		}
#endregion
	}
}