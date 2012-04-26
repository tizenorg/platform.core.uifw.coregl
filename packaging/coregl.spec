Name: coregl
Version: 0.1.1
Release: 1
ExclusiveArch:  %arm
Summary: coregl
Group: TO_BE/FILLED_IN
License: TO_BE/FILLED_IN
URL: http://www.enlightenment.org
Source0: %{name}-%{version}.tar.bz2
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

%description
This package contains the ….

%prep
%setup -q -n %{name}-%{version}

%build
cmake . -DCMAKE_INSTALL_PREFIX=/usr

make %{?jobs:-j%jobs}

%install

mkdir -p %{buildroot}/usr/lib
mkdir -p %{buildroot}/usr/include/EGL
mkdir -p %{buildroot}/usr/include/GLES2
cp %{_builddir}/%{name}-%{version}/libCOREGL.so %{buildroot}%{_libdir}/libCOREGL.so

%clean
rm -rf %{buildroot}

%post

init_coregl()
{
    cd /usr/lib/

#    file="./libEGL.so"
#    if [ -e $file ]; then
            rm -f ./libEGL.*
            rm -f ./libGLESv2.*

            ln -s libCOREGL.so libGLESv2.so.2.0
            ln -s libCOREGL.so libGLESv2.so.2
            ln -s libCOREGL.so libGLESv2.so

            ln -s libCOREGL.so libEGL.so.1.4
            ln -s libCOREGL.so libEGL.so.1
            ln -s libCOREGL.so libEGL.so
#    fi

    cd -
}

init_coregl
%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/libCOREGL.so

%doc
%changelog
Wed Feb 01 2012 MB lee <mb1.lee@ppk.com> 0.0.1-10
- Resolves #438610
