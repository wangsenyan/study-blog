class VisualComponent {
    public:
      VisualComponent();
      virtual void Draw();
      virtual void Resize();
      //...
};

class Decorator:public VisualComponent {
    public:
        Decorator(VisualComponent *);
        virtual void Draw();
        virtual void Resize();
        //...
    private:
        VisualComponent *_component;
};

void Decorator::Draw()
{
    _component->Draw();
}
void Decorator::Resize()
{
    _component->Resize();
}

class BorderDecorator:public Decorator{
    public:
        BorderDecorator(VisualComponent *, int borderWidth);
        virtual void Draw();
    private:
        void DrawBorder(int);
    private:
        int _width;
};

void BorderDecorator::Draw(){
    Decorator::Draw();
    DrawBorder(_width);
}

class ScrollDecorator:public Decorator{
    public:
        ScrollDecorator(VisualComponent *, int borderWidth);
        virtual void Draw();
    private:
        void DrawScroll(int);
    private:
        int _width;
};

void ScrollDecorator::Draw(){
    Decorator::Draw();
    DrawScroll(_width);
}

void Window::SetContents(VisualComponent *content){
    //...
}

Window *window = new Window;
TextView *textView = new textView;
window->SetContents(new BorderDecorator(new ScrollDecorator(textView), 1));