// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst {

	using System;
	using System.Collections;
	using System.Runtime.InteropServices;

#region Autogenerated code
	public partial class Registry : Gst.Object {

		public Registry(IntPtr raw) : base(raw) {}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void PluginAddedSignalDelegate (IntPtr inst, IntPtr arg0, IntPtr gch);

		static void PluginAddedSignalCallback (IntPtr inst, IntPtr arg0, IntPtr gch)
		{
			Gst.PluginAddedArgs args = new Gst.PluginAddedArgs ();
			try {
				Gst.GLib.Signal sig = ((GCHandle) gch).Target as Gst.GLib.Signal;
				if (sig == null)
					throw new Exception("Unknown signal GC handle received " + gch);

				args.Args = new object[1];
				args.Args[0] = Gst.GLib.Object.GetObject(arg0) as Gst.Plugin;
				Gst.PluginAddedHandler handler = (Gst.PluginAddedHandler) sig.Handler;
				handler (Gst.GLib.Object.GetObject (inst), args);
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[Gst.GLib.Signal("plugin-added")]
		public event Gst.PluginAddedHandler PluginAdded {
			add {
				Gst.GLib.Signal sig = Gst.GLib.Signal.Lookup (this, "plugin-added", new PluginAddedSignalDelegate(PluginAddedSignalCallback));
				sig.AddDelegate (value);
			}
			remove {
				Gst.GLib.Signal sig = Gst.GLib.Signal.Lookup (this, "plugin-added", new PluginAddedSignalDelegate(PluginAddedSignalCallback));
				sig.RemoveDelegate (value);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void FeatureAddedSignalDelegate (IntPtr inst, IntPtr arg0, IntPtr gch);

		static void FeatureAddedSignalCallback (IntPtr inst, IntPtr arg0, IntPtr gch)
		{
			Gst.FeatureAddedArgs args = new Gst.FeatureAddedArgs ();
			try {
				Gst.GLib.Signal sig = ((GCHandle) gch).Target as Gst.GLib.Signal;
				if (sig == null)
					throw new Exception("Unknown signal GC handle received " + gch);

				args.Args = new object[1];
				args.Args[0] = Gst.GLib.Object.GetObject(arg0) as Gst.PluginFeature;
				Gst.FeatureAddedHandler handler = (Gst.FeatureAddedHandler) sig.Handler;
				handler (Gst.GLib.Object.GetObject (inst), args);
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[Gst.GLib.Signal("feature-added")]
		public event Gst.FeatureAddedHandler FeatureAdded {
			add {
				Gst.GLib.Signal sig = Gst.GLib.Signal.Lookup (this, "feature-added", new FeatureAddedSignalDelegate(FeatureAddedSignalCallback));
				sig.AddDelegate (value);
			}
			remove {
				Gst.GLib.Signal sig = Gst.GLib.Signal.Lookup (this, "feature-added", new FeatureAddedSignalDelegate(FeatureAddedSignalCallback));
				sig.RemoveDelegate (value);
			}
		}

		static PluginAddedNativeDelegate PluginAdded_cb_delegate;
		static PluginAddedNativeDelegate PluginAddedVMCallback {
			get {
				if (PluginAdded_cb_delegate == null)
					PluginAdded_cb_delegate = new PluginAddedNativeDelegate (PluginAdded_cb);
				return PluginAdded_cb_delegate;
			}
		}

		static void OverridePluginAdded (Gst.GLib.GType gtype)
		{
			OverridePluginAdded (gtype, PluginAddedVMCallback);
		}

		static void OverridePluginAdded (Gst.GLib.GType gtype, PluginAddedNativeDelegate callback)
		{
			GstRegistryClass class_iface = GetClassStruct (gtype, false);
			class_iface.PluginAdded = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void PluginAddedNativeDelegate (IntPtr inst, IntPtr plugin);

		static void PluginAdded_cb (IntPtr inst, IntPtr plugin)
		{
			try {
				Registry __obj = Gst.GLib.Object.GetObject (inst, false) as Registry;
				__obj.OnPluginAdded (Gst.GLib.Object.GetObject(plugin) as Gst.Plugin);
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Registry), ConnectionMethod="OverridePluginAdded")]
		protected virtual void OnPluginAdded (Gst.Plugin plugin)
		{
			InternalPluginAdded (plugin);
		}

		private void InternalPluginAdded (Gst.Plugin plugin)
		{
			PluginAddedNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).PluginAdded;
			if (unmanaged == null) return;

			unmanaged (this.Handle, plugin == null ? IntPtr.Zero : plugin.Handle);
		}

		static FeatureAddedNativeDelegate FeatureAdded_cb_delegate;
		static FeatureAddedNativeDelegate FeatureAddedVMCallback {
			get {
				if (FeatureAdded_cb_delegate == null)
					FeatureAdded_cb_delegate = new FeatureAddedNativeDelegate (FeatureAdded_cb);
				return FeatureAdded_cb_delegate;
			}
		}

		static void OverrideFeatureAdded (Gst.GLib.GType gtype)
		{
			OverrideFeatureAdded (gtype, FeatureAddedVMCallback);
		}

		static void OverrideFeatureAdded (Gst.GLib.GType gtype, FeatureAddedNativeDelegate callback)
		{
			GstRegistryClass class_iface = GetClassStruct (gtype, false);
			class_iface.FeatureAdded = callback;
			OverrideClassStruct (gtype, class_iface);
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void FeatureAddedNativeDelegate (IntPtr inst, IntPtr feature);

		static void FeatureAdded_cb (IntPtr inst, IntPtr feature)
		{
			try {
				Registry __obj = Gst.GLib.Object.GetObject (inst, false) as Registry;
				__obj.OnFeatureAdded (Gst.GLib.Object.GetObject(feature) as Gst.PluginFeature);
			} catch (Exception e) {
				Gst.GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[Gst.GLib.DefaultSignalHandler(Type=typeof(Gst.Registry), ConnectionMethod="OverrideFeatureAdded")]
		protected virtual void OnFeatureAdded (Gst.PluginFeature feature)
		{
			InternalFeatureAdded (feature);
		}

		private void InternalFeatureAdded (Gst.PluginFeature feature)
		{
			FeatureAddedNativeDelegate unmanaged = GetClassStruct (this.LookupGType ().GetThresholdType (), true).FeatureAdded;
			if (unmanaged == null) return;

			unmanaged (this.Handle, feature == null ? IntPtr.Zero : feature.Handle);
		}

		[StructLayout (LayoutKind.Sequential)]
		struct GstRegistryClass {
			public PluginAddedNativeDelegate PluginAdded;
			public FeatureAddedNativeDelegate FeatureAdded;
			[MarshalAs (UnmanagedType.ByValArray, SizeConst=4)]
			public IntPtr[] GstReserved;
		}

		static uint class_offset = ((Gst.GLib.GType) typeof (Gst.Object)).GetClassSize ();
		static Hashtable class_structs;

		static GstRegistryClass GetClassStruct (Gst.GLib.GType gtype, bool use_cache)
		{
			if (class_structs == null)
				class_structs = new Hashtable ();

			if (use_cache && class_structs.Contains (gtype))
				return (GstRegistryClass) class_structs [gtype];
			else {
				IntPtr class_ptr = new IntPtr (gtype.GetClassPtr ().ToInt64 () + class_offset);
				GstRegistryClass class_struct = (GstRegistryClass) Marshal.PtrToStructure (class_ptr, typeof (GstRegistryClass));
				if (use_cache)
					class_structs.Add (gtype, class_struct);
				return class_struct;
			}
		}

		static void OverrideClassStruct (Gst.GLib.GType gtype, GstRegistryClass class_struct)
		{
			IntPtr class_ptr = new IntPtr (gtype.GetClassPtr ().ToInt64 () + class_offset);
			Marshal.StructureToPtr (class_struct, class_ptr, false);
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_get_path_list(IntPtr raw);

		public string[] PathList { 
			get {
				IntPtr raw_ret = gst_registry_get_path_list(Handle);
				string[] ret = (string[]) Gst.GLib.Marshaller.ListPtrToArray (raw_ret, typeof(Gst.GLib.List), true, false, typeof(string));
				return ret;
			}
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_registry_remove_feature(IntPtr raw, IntPtr feature);

		public void RemoveFeature(Gst.PluginFeature feature) {
			gst_registry_remove_feature(Handle, feature == null ? IntPtr.Zero : feature.Handle);
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_feature_filter(IntPtr raw, GstSharp.PluginFeatureFilterNative filter, bool first, IntPtr user_data);

		public Gst.PluginFeature[] FeatureFilter(Gst.PluginFeatureFilter filter, bool first) {
			GstSharp.PluginFeatureFilterWrapper filter_wrapper = new GstSharp.PluginFeatureFilterWrapper (filter);
			IntPtr raw_ret = gst_registry_feature_filter(Handle, filter_wrapper.NativeDelegate, first, IntPtr.Zero);
			Gst.PluginFeature[] ret = (Gst.PluginFeature[]) Gst.GLib.Marshaller.ListPtrToArray (raw_ret, typeof(Gst.GLib.List), true, true, typeof(Gst.PluginFeature));
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern bool gst_update_registry();

		public static bool UpdateDefault() {
			bool raw_ret = gst_update_registry();
			bool ret = raw_ret;
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern bool gst_registry_add_plugin(IntPtr raw, IntPtr plugin);

		public bool AddPlugin(Gst.Plugin plugin) {
			bool raw_ret = gst_registry_add_plugin(Handle, plugin == null ? IntPtr.Zero : plugin.Handle);
			bool ret = raw_ret;
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern bool gst_registry_scan_path(IntPtr raw, IntPtr path);

		public bool ScanPath(string path) {
			IntPtr native_path = Gst.GLib.Marshaller.StringToPtrGStrdup (path);
			bool raw_ret = gst_registry_scan_path(Handle, native_path);
			bool ret = raw_ret;
			Gst.GLib.Marshaller.Free (native_path);
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_registry_add_path(IntPtr raw, IntPtr path);

		public void AddPath(string path) {
			IntPtr native_path = Gst.GLib.Marshaller.StringToPtrGStrdup (path);
			gst_registry_add_path(Handle, native_path);
			Gst.GLib.Marshaller.Free (native_path);
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_registry_remove_plugin(IntPtr raw, IntPtr plugin);

		public void RemovePlugin(Gst.Plugin plugin) {
			gst_registry_remove_plugin(Handle, plugin == null ? IntPtr.Zero : plugin.Handle);
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_get_default();

		public static Gst.Registry Default { 
			get {
				IntPtr raw_ret = gst_registry_get_default();
				Gst.Registry ret = Gst.GLib.Object.GetObject(raw_ret) as Gst.Registry;
				return ret;
			}
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_get_feature_list_by_plugin(IntPtr raw, IntPtr name);

		public Gst.PluginFeature[] GetFeatureListByPlugin(string name) {
			IntPtr native_name = Gst.GLib.Marshaller.StringToPtrGStrdup (name);
			IntPtr raw_ret = gst_registry_get_feature_list_by_plugin(Handle, native_name);
			Gst.PluginFeature[] ret = (Gst.PluginFeature[]) Gst.GLib.Marshaller.ListPtrToArray (raw_ret, typeof(Gst.GLib.List), true, true, typeof(Gst.PluginFeature));
			Gst.GLib.Marshaller.Free (native_name);
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_get_feature_list(IntPtr raw, IntPtr type);

		public Gst.PluginFeature[] GetFeatureList(Gst.GLib.GType type) {
			IntPtr raw_ret = gst_registry_get_feature_list(Handle, type.Val);
			Gst.PluginFeature[] ret = (Gst.PluginFeature[]) Gst.GLib.Marshaller.ListPtrToArray (raw_ret, typeof(Gst.GLib.List), true, true, typeof(Gst.PluginFeature));
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern bool gst_registry_add_feature(IntPtr raw, IntPtr feature);

		public bool AddFeature(Gst.PluginFeature feature) {
			bool raw_ret = gst_registry_add_feature(Handle, feature == null ? IntPtr.Zero : feature.Handle);
			bool ret = raw_ret;
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_lookup(IntPtr raw, IntPtr filename);

		public Gst.Plugin Lookup(string filename) {
			IntPtr native_filename = Gst.GLib.Marshaller.StringToPtrGStrdup (filename);
			IntPtr raw_ret = gst_registry_lookup(Handle, native_filename);
			Gst.Plugin ret = Gst.GLib.Object.GetObject(raw_ret, true) as Gst.Plugin;
			Gst.GLib.Marshaller.Free (native_filename);
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_lookup_feature(IntPtr raw, IntPtr name);

		public Gst.PluginFeature LookupFeature(string name) {
			IntPtr native_name = Gst.GLib.Marshaller.StringToPtrGStrdup (name);
			IntPtr raw_ret = gst_registry_lookup_feature(Handle, native_name);
			Gst.PluginFeature ret = Gst.GLib.Object.GetObject(raw_ret, true) as Gst.PluginFeature;
			Gst.GLib.Marshaller.Free (native_name);
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_plugin_filter(IntPtr raw, GstSharp.PluginFilterNative filter, bool first, IntPtr user_data);

		public Gst.Plugin[] PluginFilter(Gst.PluginFilter filter, bool first) {
			GstSharp.PluginFilterWrapper filter_wrapper = new GstSharp.PluginFilterWrapper (filter);
			IntPtr raw_ret = gst_registry_plugin_filter(Handle, filter_wrapper.NativeDelegate, first, IntPtr.Zero);
			Gst.Plugin[] ret = (Gst.Plugin[]) Gst.GLib.Marshaller.ListPtrToArray (raw_ret, typeof(Gst.GLib.List), true, true, typeof(Gst.Plugin));
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_get_plugin_list(IntPtr raw);

		public Gst.Plugin[] PluginList { 
			get {
				IntPtr raw_ret = gst_registry_get_plugin_list(Handle);
				Gst.Plugin[] ret = (Gst.Plugin[]) Gst.GLib.Marshaller.ListPtrToArray (raw_ret, typeof(Gst.GLib.List), true, true, typeof(Gst.Plugin));
				return ret;
			}
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_find_plugin(IntPtr raw, IntPtr name);

		public Gst.Plugin FindPlugin(string name) {
			IntPtr native_name = Gst.GLib.Marshaller.StringToPtrGStrdup (name);
			IntPtr raw_ret = gst_registry_find_plugin(Handle, native_name);
			Gst.Plugin ret = Gst.GLib.Object.GetObject(raw_ret, true) as Gst.Plugin;
			Gst.GLib.Marshaller.Free (native_name);
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_find_feature(IntPtr raw, IntPtr name, IntPtr type);

		public Gst.PluginFeature FindFeature(string name, Gst.GLib.GType type) {
			IntPtr native_name = Gst.GLib.Marshaller.StringToPtrGStrdup (name);
			IntPtr raw_ret = gst_registry_find_feature(Handle, native_name, type.Val);
			Gst.PluginFeature ret = Gst.GLib.Object.GetObject(raw_ret, true) as Gst.PluginFeature;
			Gst.GLib.Marshaller.Free (native_name);
			return ret;
		}

		[DllImport("libgstreamer-0.10.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_registry_get_type();

		public static new Gst.GLib.GType GType { 
			get {
				IntPtr raw_ret = gst_registry_get_type();
				Gst.GLib.GType ret = new Gst.GLib.GType(raw_ret);
				return ret;
			}
		}

#endregion
#region Customized extensions
#line 1 "Registry.custom"
public Registry() : base (IntPtr.Zero)
{
  CreateNativeObject (new string [0], new Gst.GLib.Value [0]);
}

#endregion
	}
}