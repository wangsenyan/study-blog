Handle& Handle::operator = (const Handle& other){
    other._body->Ref();
    _body->Unref();
    if(_body->RefCount()==0)
        delete _body;
    _body = other._body;
    return *this;
}

class Window {
    public:
        Window(View *contents);
        // request handled by window
        virtual void DrawContents();
        virtual void Open();
        virtual void Close();
        virtual void Iconify();
        virtual void Deiconify();

       // requests forwarded to implementation
        virtual void SetOrigin(const Point &at);
        virtual void SetExtent(const Point &extent);
        virtual void Raise();
        virtual void Lower();
        virtual void DrawLine(const Point &, const Point &);
        virtual void DrawRect(const Point &, const Point &);
        virtual void DrawPolygon(const Point[], int n);
        virtual void DrawText(const char *, const Point &);
    protected:
        WindowImp *GetWindowImp();
        View *GetView();
    private:
        WindowImp *_imp;
        View *_contents;
};

class WindowImp {
    public:
        virtual void ImpTop() = 0;
        virtual void ImpBottom() = 0;
        virtual void ImpSetExtent(const Point &) = 0;
        virtual void ImpSetOrigin(const Point &) = 0;

        virtual void DeviceRect(Coord, Coord, Coord, Coord) = 0;
        virtual void DeviceText(const char *, Coord, Coord) = 0;
        virtual void DeviceBitmap(const char *, Coord, Coord) = 0;
        //lots more function for drawing on windows
    protected:
        WindowImp();
};

class ApplicationWindow: public Window {
    public:
        //...
        virtual void DrawContents();
};
void ApplicationWindow::DrawContents(){
    GetView()->DrawOn(this);
}

class IconWindow:public Window {
    public:
    //...
        virtual void DrawContents();
    private:
        const char *_bitmapName;
};

void IconWindow::DrawContents(){
    WindowImp *imp = GetWindowImp();
    if(imp!=0)
        imp->DeviceBitmap(_bitmapName, 0.0, 0.0);
}

void Window::DrawRect(const Point&p1,const Point&p2)
{
    WindowImp *imp = GetWindowImp();
    imp->DeviceRect(p1.x(), p1.y(), p2.x(), p2.y());
}

class XWindowImp:public WindowImp {
    public:
        XWindowImp();
        virtual void DeviceRect(Coord, Coord, Coord, Coord);
    private:
        Display *_dpy;
        Drawable _winid;
        GC _gc;5
};

WindowImp *Window::GetWindowImp(){
    if(_imp==0)
        _imp = WindowSystemFactory::Instance()->MakeWindowImp();
    return _imp;
}