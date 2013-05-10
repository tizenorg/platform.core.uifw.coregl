Name: coregl
Version: 0.1.8
Release: 1
ExclusiveArch:  %arm
Summary: coregl
Group: Graphics
License: TO_BE/FILLED_IN
URL: http://www.tizen.org
Source0: %{name}-%{version}.tar.gz
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
#Patch1: patchfile.patch
%ifarch %{ix86}
BuildRequires:  simulator-opengl-devel
%else
BuildRequires:  pkgconfig(gles11)
BuildRequires:  pkgconfig(gles20)
BuildRequires:  pkgconfig(xfixes)
BuildRequires:  opengl-es-devel
%endif
BuildRequires:  pkgconfig(x11)
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)

%description
This package contains the GLESv2.0/EGL 

%prep
%setup -q -n %{name}-%{version}

%build
cmake . -DCMAKE_INSTALL_PREFIX=/usr

make %{?jobs:-j%jobs}

%install

mkdir -p %{buildroot}/usr/lib
mkdir -p %{buildroot}/usr/include/EGL
mkdir -p %{buildroot}/usr/include/GLES2
cp %{_builddir}/%{name}-%{version}/libCOREGL.so.3.0 %{buildroot}%{_libdir}/libCOREGL.so.3.0
cp %{_builddir}/%{name}-%{version}/libEGL.so.1.4 %{buildroot}%{_libdir}/libEGL.so.1.4
cp %{_builddir}/%{name}-%{version}/libGLESv2.so.2.0 %{buildroot}%{_libdir}/libGLESv2.so.2.0

%clean
rm -rf %{buildroot}

%post

init_coregl()
{
    cd /usr/lib/

    rm -f ./libEGL.so
    rm -f ./libEGL.so.1
    rm -f ./libGLESv2.so
    rm -f ./libGLESv2.so.2
    rm -f ./libCOREGL.so
    rm -f ./libCOREGL.so.3
    ln -s libCOREGL.so.3.0 libCOREGL.so.3
    ln -s libCOREGL.so.3 libCOREGL.so
    ln -s libEGL.so.1.4 libEGL.so.1
    ln -s libEGL.so.1 libEGL.so
    ln -s libGLESv2.so.2.0 libGLESv2.so.2
    ln -s libGLESv2.so.2 libGLESv2.so

    cd -
}

init_coregl
%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/libCOREGL.so*
%{_libdir}/libEGL.so*
%{_libdir}/libGLESv2.so*
