%define BYPASS_COREGL 0

Name:			coregl
Summary:		CoreGL FastPath Optimization
Version:		0.1.10
Release:		02
Group:			Graphics
License:		Apache-2.0 and MIT and SGI-B-2.0 and Zlib
URL:			http://www.tizen.org
Source:			%{name}-%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(libpng)

%global TZ_SYS_RO_SHARE	%{?TZ_SYS_RO_SHARE:%TZ_SYS_RO_SHARE}%{!?TZ_SYS_RO_SHARE:/usr/share}

%description
CoreGL provides the following capabilities:
- Support for driver-independent optimization (FastPath)
- EGL/OpenGL ES debugging
- Performance logging

Supported versions:
- EGL 1.4
- OpenGL ES 2.0, 3.0, 3.1

%package devel
Summary:		Development files for EGL 1.4 and OpenGL ES 1.1 and 2.0
Group:			Graphics
Requires:		%{name} = %{version}-%{release}
Requires:		libgbm-devel
Requires:		libwayland-egl

%description devel
This package contains the development libraries and header files needed by
packages that requires OpenGL ES 1.1 or 2.0 acceleration.


%prep
%setup -q -n %{name}-%{version}

%build
%if "%{BYPASS_COREGL}" != "1"
cmake . -DCMAKE_INSTALL_PREFIX=/usr %{?extra_option}
make %{?jobs:-j%jobs}
%endif

%install

# for license notification
mkdir -p %{buildroot}/%{TZ_SYS_RO_SHARE}/license
cp -a %{_builddir}/%{buildsubdir}/COPYING %{buildroot}/%{TZ_SYS_RO_SHARE}/license/%{name}
cp -a %{_builddir}/%{buildsubdir}/COPYING.MIT %{buildroot}/%{TZ_SYS_RO_SHARE}/license/%{name}.MIT
cp -a %{_builddir}/%{buildsubdir}/COPYING.SGIFreeSWLicB_2_0 %{buildroot}/%{TZ_SYS_RO_SHARE}/license/%{name}.SGIFreeSWLicB_2_0
cp -a %{_builddir}/%{buildsubdir}/COPYING.ZLIB %{buildroot}/%{TZ_SYS_RO_SHARE}/license/%{name}.ZLIB

# release pkg
mkdir -p %{buildroot}%{_libdir}/pkgconfig

%if "%{BYPASS_COREGL}" != "1"
cp libCOREGL.so.4.0					%{buildroot}%{_libdir}/
ln -sf libCOREGL.so.4.0				%{buildroot}%{_libdir}/libCOREGL.so.4
ln -sf libCOREGL.so.4				%{buildroot}%{_libdir}/libCOREGL.so
cp libEGL.so.1.4					%{buildroot}%{_libdir}/
cp libGLESv2.so.2.0					%{buildroot}%{_libdir}/
cp libGLESv1_CM.so.1.1				%{buildroot}%{_libdir}/
%else
ln -sf driver/libEGL.so.1.4			%{buildroot}%{_libdir}/libEGL.so.1.4
ln -sf driver/libGLESv2.so.2.0		%{buildroot}%{_libdir}/libGLESv2.so.2.0
ln -sf driver/libGLESv1_CM.so.1.1	%{buildroot}%{_libdir}/libGLESv1_CM.so.1.1
%endif
ln -sf libEGL.so.1.4				%{buildroot}%{_libdir}/libEGL.so.1
ln -sf libEGL.so.1					%{buildroot}%{_libdir}/libEGL.so
ln -sf libGLESv2.so.2.0				%{buildroot}%{_libdir}/libGLESv2.so.2
ln -sf libGLESv2.so.2				%{buildroot}%{_libdir}/libGLESv2.so
ln -sf libGLESv1_CM.so.1.1			%{buildroot}%{_libdir}/libGLESv1_CM.so.1
ln -sf libGLESv1_CM.so.1			%{buildroot}%{_libdir}/libGLESv1_CM.so

# devel pkg
mkdir -p %{buildroot}%{_includedir}
cp -a include_KHR/EGL				%{buildroot}%{_includedir}
cp -a include_KHR/GLES				%{buildroot}%{_includedir}
cp -a include_KHR/GLES2				%{buildroot}%{_includedir}
cp -a include_KHR/GLES3				%{buildroot}%{_includedir}
cp -a include_KHR/KHR				%{buildroot}%{_includedir}
cp -a pkgconfig/*.pc				%{buildroot}%{_libdir}/pkgconfig/

%clean
rm -rf %{buildroot}

%post
cd %{_libdir}
ln -sf libGLESv1_CM.so.1.1 libGLESv1_CM.so.1
ln -sf libGLESv1_CM.so.1 libGLESv1_CM.so

%postun
cd %{_libdir}
rm -rf libGLESv1_CM.so
rm -rf libGLESv1_CM.so.1
/sbin/ldconfig > /dev/null 2>&1

%files
%manifest packaging/coregl.manifest
%defattr(-,root,root,-)
%if "%{BYPASS_COREGL}" != "1"
%{_libdir}/libCOREGL.so*
%endif
%{_libdir}/libEGL.so*
%{_libdir}/libGLESv2.so*
%{_libdir}/libGLESv1_CM.so*
%{TZ_SYS_RO_SHARE}/license/%{name}
%{TZ_SYS_RO_SHARE}/license/%{name}.MIT
%{TZ_SYS_RO_SHARE}/license/%{name}.SGIFreeSWLicB_2_0
%{TZ_SYS_RO_SHARE}/license/%{name}.ZLIB

%files devel
%defattr(-,root,root,-)
%{_includedir}/EGL/*
%{_includedir}/GLES/*
%{_includedir}/GLES2/*
%{_includedir}/GLES3/*
%{_includedir}/KHR/*
%{_libdir}/pkgconfig/*.pc
