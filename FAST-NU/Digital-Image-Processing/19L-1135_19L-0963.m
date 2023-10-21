function varargout = gui(varargin)
% GUI MATLAB code for gui.fig
%      GUI, by itself, creates a new GUI or raises the existing
%      singleton*.
%
%      H = GUI returns the handle to a new GUI or the handle to
%      the existing singleton*.
%
%      GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI.M with the given input arguments.
%
%      GUI('Property','Value',...) creates a new GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before gui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to gui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help gui

% Last Modified by GUIDE v2.5 29-May-2022 19:16:21

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @gui_OpeningFcn, ...
                   'gui_OutputFcn',  @gui_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before gui is made visible.
function gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to gui (see VARARGIN)

% Choose default command line output for gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = gui_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)

[rawname, rawpath] = uigetfile({'C:\Users\hassa\Desktop\*.Jpg*'}, 'Select Image Data');
fullname = [rawpath rawname];
set(handles.edit1, 'String', fullname);
global filename;
filename = fullname;

im = imread(fullname);
set(handles.axes3,'Units','pixels');
resizePos = get(handles.axes3,'Position');
myImage= imresize(im, [resizePos(3) resizePos(3)]);
axes(handles.axes3);
imshow(myImage);
set(handles.axes3,'Units','normalized');


function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes when figure1 is resized.
function figure1_SizeChangedFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
n = 8
m = 8
global filename;
dct1(filename,n,m);



function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double


% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function r_Callback(hObject, eventdata, handles)
% hObject    handle to r (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of r as text
%        str2double(get(hObject,'String')) returns contents of r as a double


% --- Executes during object creation, after setting all properties.
function r_CreateFcn(hObject, eventdata, handles)
% hObject    handle to r (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end






function[]=dct1(filename,n,m)
N=8;                        
M=8;
I=imread(filename);         
iDim=size(I);              
iTransform.block=zeros(N,M);  
normalizeMatrix=[16 11 10 16 24 40 51 61 
          12 12 14 19 26 58 60 55
          14 13 16 24 40 57 69 56
          14 17 22 29 51 87 80 62
          18 22 37 56 68 109 103 77
          24 35 55 64 81 104 113 92
          49 64 78 87 103 121 120 101
          72 92 95 98 112 100 103 99];
 
save('C:\Users\hassa\Desktop\jpegCompression.txt','I');

for a=1:iDim(1)/N
    for b=1:iDim(2)/M
        for k=1:N
            for l=1:M
                prod=0;
                for i=1:N
                    for j=1:M
                        prod=prod+double(I(N*(a-1)+i,M*(b-1)+j))*cos(pi*(k-1)*(2*i-1)/(2*N))*cos(pi*(l-1)*(2*j-1)/(2*M));
                    end
                end
                if k==1
                    prod=prod*sqrt(1/N);
                else
                    prod=prod*sqrt(2/N);
                end
                if l==1
                    prod=prod*sqrt(1/M);
                else
                    prod=prod*sqrt(2/M);
                end
                iTransform(a,b).block(k,l)=prod;
            end
        end
        
        iTransform(a,b).block=round(iTransform(a,b).block./normalizeMatrix);
    end
end

for a=1:iDim(1)/N
    for b=1:iDim(2)/M
        iZigZag(a,b).block=zeros(1,0);
        frequencySum=2:(N+M);
        counter=1;
        for i=1:length(frequencySum)
            if i<=((length(frequencySum)+1)/2)
                if rem(i,2)~=0
                    xIndices=counter:frequencySum(i)-counter;
                else
                    xIndices=frequencySum(i)-counter:-1:counter;
                end
                    indexLength=length(xIndices);
                    yIndices=xIndices(indexLength:-1:1);
                    for p=1:indexLength
                        if iTransform(a,b).block(xIndices(p),yIndices(p))<0
                            binEq=dec2bin(bitxor(2^n-1,abs(iTransform(a,b).block(xIndices(p),yIndices(p)))),n);
                        else
                            binEq=dec2bin(iTransform(a,b).block(xIndices(p),yIndices(p)),n);
                        end
                        iZigZag(a,b).block=[iZigZag(a,b).block,binEq(1:m)];
                    end
            else
                counter=counter+1;
                if rem(i,2)~=0
                    xIndices=counter:frequencySum(i)-counter;
                else
                    xIndices=frequencySum(i)-counter:-1:counter;
                end
                    indexLength=length(xIndices);
                    yIndices=xIndices(indexLength:-1:1); 
                    for p=1:indexLength
                        if iTransform(a,b).block(xIndices(p),yIndices(p))<0
                            binEq=dec2bin(bitxor(2^n-1,abs(iTransform(a,b).block(xIndices(p),yIndices(p)))),n);
                        else
                            binEq=dec2bin(iTransform(a,b).block(xIndices(p),yIndices(p)),n);
                        end
                        iZigZag(a,b).block=[iZigZag(a,b).block,binEq(1:m)];
                    end
            end
        end
    end
end

clear iTransform prod; 
clear xIndices yIndices counter;

for a=1:iDim(1)/N
    for b=1:iDim(2)/M
        

        count=0;
        run=zeros(1,0);
        sym=iZigZag(a,b).block(1);
        j=1;
        blockLength=length(iZigZag(a,b).block);
        for i=1:blockLength
            if iZigZag(a,b).block(i)==sym
                count=count+1;
            else
                run.count(j)=count;
                run.sym(j)=sym;
                j=j+1;
                sym=iZigZag(a,b).block(i);
                count=1;
            end
            if i==blockLength
                run.count(j)=count;
                run.sym(j)=sym;
            end
        end 
        

        dim=length(run.count);
        maxvalue=max(run.count); 
        codelength=log2(maxvalue)+1;
        codelength=floor(codelength);
        

        I_runcode(a,b).code=zeros(1,0);
        for i=1:dim
            I_runcode(a,b).code=[I_runcode(a,b).code,dec2bin(run.count(i),codelength),run.sym(i)];
        end
    end
end

save ('C:\Users\hassa\Desktop\jpegCompression.txt','I_runcode');

clear iZigZag run;

for a=1:iDim(1)/N
    for b=1:iDim(2)/M
        encodedString=I_runcode(a,b).code;
        
        encodedLength=length(encodedString);
        
        factorsMat=zeros(1,0);
        if encodedLength<=(n+1)
            realfact=encodedLength;
        else
            for i=2:encodedLength-2 
                if(rem(encodedLength,i)==0)
                    factorsMat=[factorsMat,i];
                end
            end

            for i=1:length(factorsMat)
                flagCenter=0;
                tempDim=encodedLength/factorsMat(i);
                for j=1:tempDim
                    if strcmp(encodedString(1+(j-1)*factorsMat(i):j*factorsMat(i)),dec2bin(0,factorsMat(i)))==0
                        if j==1
                            flagCenter=flagCenter+1;
                        else
                            if encodedString((j-1)*factorsMat(i))~=encodedString(j*factorsMat(i))
                                flagCenter=flagCenter+1;
                            else
                                break;
                            end
                        end
                    else
                        break;
                    end
                end
                if flagCenter==tempDim
                    realfact=factorsMat(i);
                    break;
                end
            end
        end
        

        clear factorsMat flagCenter j 

        decodedString=zeros(1,0);
        tempDim=encodedLength/realfact;
        for i=1:tempDim
            count_str=encodedString(1+(i-1)*realfact:(i*realfact)-1);
            countval=bin2dec(count_str);
            for j=1:countval
                decodedString=[decodedString,encodedString(i*realfact)];
            end
        end
        I_runcode(a,b).code=decodedString;
    end
end

clear encodedString decodedString tempDim realfact encodedLength
clear countval count_str

iRecTransform.block=zeros(N,M);
for a=1:iDim(1)/N
    for b=1:iDim(2)/M
        bpp=length(I_runcode(a,b).code)/(N*M); 
        bpp_diff=n-bpp; 
        frequencySum=2:(N+M);
        counter=1;
        cIndex=1;
        for i=1:length(frequencySum)
            if i<=((length(frequencySum)+1)/2)
                if rem(i,2)~=0
                    xIndices=counter:frequencySum(i)-counter;
                else
                    xIndices=frequencySum(i)-counter:-1:counter;
                end
                    indexLength=length(xIndices);
                    yIndices=xIndices(indexLength:-1:1);
                    for p=1:indexLength
                        decm_eq=bin2dec([I_runcode(a,b).code(1+m*(cIndex-1):m*cIndex),dec2bin(0,bpp_diff)]);
                        if decm_eq>(2^(n-1))-1
                            decm_eq=decm_eq-(2^n-1);
                        end
                        iRecTransform(a,b).block(xIndices(p),yIndices(p))=decm_eq;
                       cIndex=cIndex+1;
                    end
            else
                counter=counter+1;
                if rem(i,2)~=0
                    xIndices=counter:frequencySum(i)-counter;
                else
                    xIndices=frequencySum(i)-counter:-1:counter;
                end
                    indexLength=length(xIndices);
                    yIndices=xIndices(indexLength:-1:1);
                    for p=1:indexLength
                        decm_eq=bin2dec([I_runcode(a,b).code(1+m*(cIndex-1):m*cIndex),dec2bin(0,bpp_diff)]);
                        if decm_eq>(2^(n-1))-1
                            decm_eq=decm_eq-(2^n-1);
                        end
                        iRecTransform(a,b).block(xIndices(p),yIndices(p))=decm_eq;
                        cIndex=cIndex+1;
                    end
            end
        end
    end
end

clear I_runcode xIndices yIndices
clear cIndex frequencySum

for a=1:iDim(1)/N
    for b=1:iDim(2)/M
        iRecTransform(a,b).block=(iRecTransform(a,b).block).*normalizeMatrix;
    end
end

for a=1:iDim(1)/N
    for b=1:iDim(2)/M
        for i=1:N
            for j=1:M
                prod=0;
                for k=1:N
                    for l=1:M
                        if k==1
                           temp=double(sqrt(1/2)*iRecTransform(a,b).block(k,l))*cos(pi*(k-1)*(2*i-1)/(2*N))*cos(pi*(l-1)*(2*j-1)/(2*M));
                        else
                            temp=double(iRecTransform(a,b).block(k,l))*cos(pi*(k-1)*(2*i-1)/(2*N))*cos(pi*(l-1)*(2*j-1)/(2*M));
                        end
                        if l==1
                            temp=temp*sqrt(1/2);
                        end
                        prod=prod+temp;
                    end
                end
                prod=prod*(2/sqrt(M*N));
                I_rec((a-1)*N+i,(b-1)*M+j)=prod;
            end
        end
    end
end

clear iRecTransform

diff=im2double(I).*255-I_rec;
diff=diff/max(max(diff));
diff=im2uint8(diff);
I_rec=I_rec/max(max(I_rec));
I_rec=im2uint8(I_rec);
%figure,imshow(I_rec,[0,2^n-1]);
%figure,imshow(diff,[0 2^n-1])
figure, imhist(I_rec);
figure, imhist(diff);
