%define BYPASS_COREGL 0

Name:			coregl
Summary:		CoreGL FastPath Optimization
Version:		0.1.10
Release:		02
Group:			Graphics
License:		Apache 2.0
URL:			http://www.tizen.org
Source:			%{name}-%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(libpng)

%description
CoreGL provides the following capabilities:
- Support for driver-independent optimization (FastPath)
- EGL/OpenGL ES debugging
- Performance logging

Supported versions:
- EGL 1.4
- OpenGL ES 2.0, 3.0

%package devel
Summary:		Development files for EGL 1.4 and OpenGL ES 1.1 and 2.0
Group:			Graphics
Requires:		%{name} = %{version}-%{release}

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
# release pkg
mkdir -p %{buildroot}%{_libdir}/pkgconfig

%if "%{BYPASS_COREGL}" != "1"
cp libCOREGL.so.4.0					%{buildroot}%{_libdir}/
ln -sf libCOREGL.so.4.0				%{buildroot}%{_libdir}/libCOREGL.so.4
ln -sf libCOREGL.so.4				%{buildroot}%{_libdir}/libCOREGL.so
cp libEGL.so.1.4					%{buildroot}%{_libdir}/
cp libGLESv2.so.2.0					%{buildroot}%{_libdir}/
%else
ln -sf driver/libEGL.so.1.4			%{buildroot}%{_libdir}/libEGL.so.1.4
ln -sf driver/libGLESv2.so.2.0		%{buildroot}%{_libdir}/libGLESv2.so.2.0
%endif
ln -sf libEGL.so.1.4				%{buildroot}%{_libdir}/libEGL.so.1
ln -sf libEGL.so.1					%{buildroot}%{_libdir}/libEGL.so
ln -sf driver/libGLESv1_CM.so.1.1	%{buildroot}%{_libdir}/libGLESv1_CM.so.1.1
ln -sf libGLESv1_CM.so.1.1			%{buildroot}%{_libdir}/libGLESv1_CM.so.1
ln -sf libGLESv1_CM.so.1			%{buildroot}%{_libdir}/libGLESv1_CM.so
ln -sf libGLESv2.so.2.0				%{buildroot}%{_libdir}/libGLESv2.so.2
ln -sf libGLESv2.so.2				%{buildroot}%{_libdir}/libGLESv2.so

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

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest packaging/coregl.manifest
%defattr(-,root,root,-)
%if "%{BYPASS_COREGL}" != "1"
%{_libdir}/libCOREGL.so*
%endif
%{_libdir}/libEGL.so*
%{_libdir}/libGLESv1_CM.so*
%{_libdir}/libGLESv2.so*

%files devel
%defattr(-,root,root,-)
%{_includedir}/EGL/*
%{_includedir}/GLES/*
%{_includedir}/GLES2/*
%{_includedir}/GLES3/*
%{_includedir}/KHR/*
%{_libdir}/pkgconfig/*.pc
