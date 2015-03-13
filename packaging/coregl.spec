Name:			coregl
Summary:		CoreGL FastPath Optimization 
Version:		0.1.10
Release:		1
ExclusiveArch:	%arm
Group:			Graphics
License:		TO_BE/FILLED_IN
URL:			http://www.tizen.org
Source:			%{name}-%{version}.tar.gz

BuildRequires:  pkgconfig(gles20)
BuildRequires:  pkgconfig(xfixes)
BuildRequires:  pkgconfig(x11)
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)

%description
CoreGL provides the following capabilities:
- Support for driver-independent optimization (FastPath)
- EGL/OpenGL ES debugging
- Performance logging

Supported versions:
- EGL 1.4
- OpenGL ES 2.0, 3.0

%prep
%setup -q -n %{name}-%{version}

%build
cmake . -DCMAKE_INSTALL_PREFIX=/usr %{?extra_option}
make %{?jobs:-j%jobs}

%install
mkdir -p %{buildroot}/usr/lib
cp %{_builddir}/%{name}-%{version}/libCOREGL.so.4.0 %{buildroot}%{_libdir}/libCOREGL.so.4.0
cp %{_builddir}/%{name}-%{version}/libEGL.so.1.4 %{buildroot}%{_libdir}/libEGL.so.1.4
cp %{_builddir}/%{name}-%{version}/libGLESv2.so.2.0 %{buildroot}%{_libdir}/libGLESv2.so.2.0
ln -sf libCOREGL.so.4.0 %{buildroot}%{_libdir}/libCOREGL.so.4
ln -sf libCOREGL.so.4 %{buildroot}%{_libdir}/libCOREGL.so
ln -sf libEGL.so.1.4 %{buildroot}%{_libdir}/libEGL.so.1
ln -sf libEGL.so.1 %{buildroot}%{_libdir}/libEGL.so
ln -sf driver/libGLESv1_CM.so.1.1 %{buildroot}%{_libdir}/libGLESv1_CM.so.1.1
ln -sf libGLESv1_CM.so.1.1 %{buildroot}%{_libdir}/libGLESv1_CM.so.1
ln -sf libGLESv1_CM.so.1 %{buildroot}%{_libdir}/libGLESv1_CM.so
ln -sf libGLESv2.so.2.0 %{buildroot}%{_libdir}/libGLESv2.so.2
ln -sf libGLESv2.so.2 %{buildroot}%{_libdir}/libGLESv2.so

%clean
rm -rf %{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/libCOREGL.so*
%{_libdir}/libEGL.so*
%{_libdir}/libGLESv1_CM.so*
%{_libdir}/libGLESv2.so*
