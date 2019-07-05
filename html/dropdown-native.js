(function (root, factory) {
  if (typeof define === 'function' && define.amd) {
    define([], factory);
  } else if (typeof module === 'object' && module.exports) {
    module.exports = factory();
  } else {
    var bsn = factory();
    root.Button = bsn.Button;
    root.Dropdown = bsn.Dropdown;
  }
}(this, function () {
  var globalObject = typeof global !== 'undefined' ? global : this||window,
    doc = document.documentElement, body = document.body,
    dataToggle    = 'data-toggle',
    dataDismiss   = 'data-dismiss',
    dataSpy       = 'data-spy',
    dataRide      = 'data-ride',
    stringButton    = 'Button',
    stringDropdown  = 'Dropdown',
    databackdrop      = 'data-backdrop',
    dataKeyboard      = 'data-keyboard',
    dataTarget        = 'data-target',
    dataInterval      = 'data-interval',
    dataHeight        = 'data-height',
    dataPause         = 'data-pause',
    dataOriginalTitle = 'data-original-title',
    dataOriginalText  = 'data-original-text',
    dataDismissible   = 'data-dismissible',
    dataTrigger       = 'data-trigger',
    dataAnimation     = 'data-animation',
    dataContainer     = 'data-container',
    dataPlacement     = 'data-placement',
    dataDelay         = 'data-delay',
    dataOffsetTop     = 'data-offset-top',
    dataOffsetBottom  = 'data-offset-bottom',
  
    // option keys
    backdrop = 'backdrop', keyboard = 'keyboard', delay = 'delay',
    content = 'content', target = 'target', 
    interval = 'interval', pause = 'pause', animation = 'animation',
    placement = 'placement', container = 'container', 
  
    // box model
    offsetTop    = 'offsetTop',      offsetBottom   = 'offsetBottom',
    offsetLeft   = 'offsetLeft',
    scrollTop    = 'scrollTop',      scrollLeft     = 'scrollLeft',
    clientWidth  = 'clientWidth',    clientHeight   = 'clientHeight',
    offsetWidth  = 'offsetWidth',    offsetHeight   = 'offsetHeight',
    innerWidth   = 'innerWidth',     innerHeight    = 'innerHeight',
    scrollHeight = 'scrollHeight',   height         = 'height',
  
    // aria
    ariaExpanded = 'aria-expanded',
    ariaHidden   = 'aria-hidden',
  
    // event names
    clickEvent    = 'click',
    hoverEvent    = 'hover',
    keydownEvent  = 'keydown',
    resizeEvent   = 'resize',
    scrollEvent   = 'scroll',
    // originalEvents
    showEvent     = 'show',
    shownEvent    = 'shown',
    hideEvent     = 'hide',
    hiddenEvent   = 'hidden',
    closeEvent    = 'close',
    closedEvent   = 'closed',
    slidEvent     = 'slid',
    slideEvent    = 'slide',
    changeEvent   = 'change',
  
    // other
    getAttribute         = 'getAttribute',
    setAttribute         = 'setAttribute',
    hasAttribute         = 'hasAttribute',
    getElementsByTagName = 'getElementsByTagName',
    getBoundingClientRect= 'getBoundingClientRect',
    querySelectorAll     = 'querySelectorAll',
    getElementsByCLASSNAME = 'getElementsByClassName',
  
    indexOf      = 'indexOf',
    parentNode   = 'parentNode',
    length       = 'length',
    toLowerCase  = 'toLowerCase',
    Transition   = 'Transition',
    Webkit       = 'Webkit',
    style        = 'style',
    
    active     = 'active',
    inClass    = 'in',
    collapsing = 'collapsing',
    disabled   = 'disabled',
    loading    = 'loading',
    left       = 'left',
    right      = 'right',
    top        = 'top',
    bottom     = 'bottom',
  
    // IE8 browser detect
    isIE8 = false,
  
    // tooltip / popover
    fixedTop = 'navbar-fixed-top',
    fixedBottom = 'navbar-fixed-bottom',  
    mouseHover = ('onmouseleave' in document) ? [ 'mouseenter', 'mouseleave'] : [ 'mouseover', 'mouseout' ],
    tipPositions = /\b(top|bottom|left|top)+/,
  
    // transitionEnd since 2.0.4
    supportTransitions = Webkit+Transition in doc[style] || Transition[toLowerCase]() in doc[style],
    transitionEndEvent = Webkit+Transition in doc[style] ? Webkit[toLowerCase]()+Transition+'End' : Transition[toLowerCase]()+'end',  
  
    // set new focus element since 2.0.3
    setFocus = function(element){
      element.focus ? element.focus() : element.setActive();
    },
  
    // class manipulation, since 2.0.0 requires polyfill.js
    addClass = function(element,classNAME) {
      element.classList.add(classNAME);
    },
    removeClass = function(element,classNAME) {
      element.classList.remove(classNAME);
    },
    hasClass = function(element,classNAME){ // since 2.0.0
      return element.classList.contains(classNAME);
    },
  
    // selection methods
    nodeListToArray = function(nodeList){
      var childItems = []; for (var i = 0, nll = nodeList[length]; i<nll; i++) { childItems.push( nodeList[i] ) }
      return childItems;
    },
    getElementsByClassName = function(element,classNAME) { // getElementsByClassName IE8+
      var selectionMethod = isIE8 ? querySelectorAll : getElementsByCLASSNAME;      
      return nodeListToArray(element[selectionMethod]( isIE8 ? '.' + classNAME.replace(/\s(?=[a-z])/g,'.') : classNAME ));
    },
    queryElement = function (selector, parent) {
      var lookUp = parent ? parent : document;
      return typeof selector === 'object' ? selector : lookUp.querySelector(selector);
    },
    getClosest = function (element, selector) { //element is the element and selector is for the closest parent element to find
    // source http://gomakethings.com/climbing-up-and-down-the-dom-tree-with-vanilla-javascript/
      var firstChar = selector.charAt(0);
      for ( ; element && element !== document; element = element[parentNode] ) {// Get closest match
        if ( firstChar === '.' ) {// If selector is a class
          if ( queryElement(selector,element[parentNode]) !== null && hasClass(element,selector.replace('.','')) ) { return element; }
        } else if ( firstChar === '#' ) { // If selector is an ID
          if ( element.id === selector.substr(1) ) { return element; }
        }
      }
      return false;
    },
  
    // event attach jQuery style / trigger  since 1.2.0
    on = function (element, event, handler) {
      element.addEventListener(event, handler, false);
    },
    off = function(element, event, handler) {
      element.removeEventListener(event, handler, false);
    },
    one = function (element, event, handler) { // one since 2.0.4
      on(element, event, function handlerWrapper(e){
        handler(e);
        off(element, event, handlerWrapper);
      });
    },
    emulateTransitionEnd = function(element,handler){ // emulateTransitionEnd since 2.0.4
      if (supportTransitions) { one(element, transitionEndEvent, function(e){ handler(e); }); } 
      else { handler(); }
    },
    bootstrapCustomEvent = function (eventName, componentName, related) {
      var OriginalCustomEvent = new CustomEvent( eventName + '.bs.' + componentName);
      OriginalCustomEvent.relatedTarget = related;
      this.dispatchEvent(OriginalCustomEvent);
    },
  
    // reference a live collection of the DOM
    AllDOMElements = document[getElementsByTagName]('*'),
  
    // Init DATA API
    initializeDataAPI = function( component, constructor, dataAttribute, collection ){
      var lookUp = collection && collection[length] ? collection : AllDOMElements;
      for (var i=0; i < lookUp[length]; i++) {
        var attrValue = lookUp[i][getAttribute](dataAttribute), expectedAttrValue = component.replace(/spy/i,'')[toLowerCase]();
        if ( attrValue && component === stringButton && ( attrValue[indexOf](expectedAttrValue) > -1 )
            || attrValue === expectedAttrValue ) {
          new constructor(lookUp[i]);
        }
      }
    },  
  
    // tab / collapse stuff
    targetsReg = /^\#(.)+$/,
    getOuterHeight = function (child) {
      var childStyle = child && (child.currentStyle || globalObject.getComputedStyle(child)), 
        btp = /px/.test(childStyle.borderTopWidth) ? Math.round(childStyle.borderTopWidth.replace('px','')) : 0,
        btb = /px/.test(childStyle.borderBottomWidth) ? Math.round(childStyle.borderBottomWidth.replace('px','')) : 0,
        mtp = /px/.test(childStyle.marginTop) ? Math.round(childStyle.marginTop.replace('px','')) : 0,
        mbp = /px/.test(childStyle.marginBottom) ? Math.round(childStyle.marginBottom.replace('px','')) : 0;
      return child[clientHeight] + parseInt( btp ) + parseInt( btb ) + parseInt( mtp ) + parseInt( mbp );
    },
    getMaxHeight = function(parent) { // get collapse trueHeight and border
      var parentHeight = 0;
      for (var k = 0, ll = parent.children[length]; k < ll; k++) {
        parentHeight += getOuterHeight(parent.children[k]);
      }
      return parentHeight;
    },
  
    // tooltip / popover stuff
    isElementInViewport = function(element) { // check if this.tooltip is in viewport
      var rect = element[getBoundingClientRect]();
      return ( rect[top] >= 0 && rect[left] >= 0 &&
        rect[bottom] <= (globalObject[innerHeight] || doc[clientHeight]) &&
        rect[right] <= (globalObject[innerWidth] || doc[clientWidth]) )
    },
    getScroll = function() { // also Affix and ScrollSpy uses it
      return {
        y : globalObject.pageYOffset || doc[scrollTop],
        x : globalObject.pageXOffset || doc[scrollLeft]
      }
    },
    styleTip = function(link,element,position,parent) { // both popovers and tooltips
      var rect = link[getBoundingClientRect](), 
          scroll = parent === body ? getScroll() : { x: parent[offsetLeft] + parent[scrollLeft], y: parent[offsetTop] + parent[scrollTop] },
          linkDimensions = { w: rect[right] - rect[left], h: rect[bottom] - rect[top] },
          elementDimensions = { w : element[offsetWidth], h: element[offsetHeight] };
  
      // apply styling to tooltip or popover
      if ( position === top ) { // TOP
        element[style][top] = rect[top] + scroll.y - elementDimensions.h + 'px';
        element[style][left] = rect[left] + scroll.x - elementDimensions.w/2 + linkDimensions.w/2 + 'px'
  
      } else if ( position === bottom ) { // BOTTOM
        element[style][top] = rect[top] + scroll.y + linkDimensions.h + 'px';
        element[style][left] = rect[left] + scroll.x - elementDimensions.w/2 + linkDimensions.w/2 + 'px';
  
      } else if ( position === left ) { // LEFT
        element[style][top] = rect[top] + scroll.y - elementDimensions.h/2 + linkDimensions.h/2 + 'px';
        element[style][left] = rect[left] + scroll.x - elementDimensions.w + 'px';
  
      } else if ( position === right ) { // RIGHT
        element[style][top] = rect[top] + scroll.y - elementDimensions.h/2 + linkDimensions.h/2 + 'px';
        element[style][left] = rect[left] + scroll.x + linkDimensions.w + 'px';
      }
      element.className[indexOf](position) === -1 && (element.className = element.className.replace(tipPositions,position));
    },
    updatePlacement = function(position) {
      return position === top ? bottom : // top
             position === bottom ? top : // bottom
             position === left ? right : // left
             position === right ? left : position; // right
    };
  

  
  
  /* Native Javascript for Bootstrap 3 | Button
  ---------------------------------------------*/
  
  // BUTTON DEFINITION
  // ===================
  var Button = function( element, option ) {
  
    // initialization element
    element = queryElement(element);
  
    // set option
    option = option || null;
  
    // constant
    var toggled = false, // toggled makes sure to prevent triggering twice the change.bs.button events
  
        // strings
        component = 'button',
        checked = 'checked',
        reset = 'reset',
        LABEL = 'LABEL',
        INPUT = 'INPUT',
  
      // private methods
      setState = function() {
        if ( !! option && option !== reset ) {
          if ( option === loading ) {
            addClass(element,disabled);
            element[setAttribute](disabled,disabled);
          }
          element[setAttribute](dataOriginalText, element.innerHTML.replace(/^\s+|\s+$/g, '')); // trim the text
          element.innerHTML = element[getAttribute]('data-'+option+'-text');
        }
      },
      resetState = function() {
        if (element[getAttribute](dataOriginalText)) {
          if ( hasClass(element,disabled) || element[getAttribute](disabled) === disabled ) {
            removeClass(element,disabled);
            element.removeAttribute(disabled);
          }
          element.innerHTML = element[getAttribute](dataOriginalText);
        }
      },
      toggle = function(e) {
        var parent = e[target][parentNode],
          label = e[target].tagName === LABEL ? e[target] : parent.tagName === LABEL ? parent : null; // the .btn label
  
        if ( !label ) return; //react if a label or its immediate child is clicked
  
        var eventTarget = this, // the button group, the target of the handler function
          labels = getElementsByClassName(eventTarget,'btn'), // all the button group buttons
          input = label[getElementsByTagName](INPUT)[0];
  
        if ( !input ) return; //return if no input found
  
        // manage the dom manipulation
        if ( input.type === 'checkbox' ) { //checkboxes
          if ( !input[checked] ) {
            addClass(label,active);
            input[getAttribute](checked);
            input[setAttribute](checked,checked);
            input[checked] = true;
          } else {
            removeClass(label,active);
            input[getAttribute](checked);
            input.removeAttribute(checked);
            input[checked] = false;
          }
  
          if (!toggled) { // prevent triggering the event twice
            toggled = true;
            bootstrapCustomEvent.call(input, changeEvent, component); //trigger the change for the input
            bootstrapCustomEvent.call(element, changeEvent, component); //trigger the change for the btn-group
          }
        }
  
        if ( input.type === 'radio' && !toggled ) { // radio buttons
          if ( !input[checked] ) { // don't trigger if already active
            addClass(label,active);
            input[setAttribute](checked,checked);
            input[checked] = true;
            bootstrapCustomEvent.call(input, changeEvent, component); //trigger the change for the input
            bootstrapCustomEvent.call(element, changeEvent, component); //trigger the change for the btn-group
  
            toggled = true;
            for (var i = 0, ll = labels[length]; i<ll; i++) {
              var otherLabel = labels[i], otherInput = otherLabel[getElementsByTagName](INPUT)[0];
              if ( otherLabel !== label && hasClass(otherLabel,active) )  {
                removeClass(otherLabel,active);
                otherInput.removeAttribute(checked);
                otherInput[checked] = false;
                bootstrapCustomEvent.call(otherInput, changeEvent, component); // trigger the change
              }
            }
          }
        }
        setTimeout( function() { toggled = false; }, 50 );
      };
  
    // init
    if ( hasClass(element,'btn') ) { // when Button text is used we execute it as an instance method
      if ( option !== null ) {
        if ( option !== reset ) { setState(); } 
        else { resetState(); }
      }
    }
    if ( hasClass(element,'btn-group') ) {
      if ( !( stringButton in element ) ) { // prevent adding event handlers twice
        on( element, clickEvent, toggle );
      }
      element[stringButton] = this;
    }
  };
  
  // BUTTON DATA API
  // =================
  initializeDataAPI( stringButton, Button, dataToggle );
  
  
  
  /* Native Javascript for Bootstrap 3 | Dropdown
  ----------------------------------------------*/
  
  // DROPDOWN DEFINITION
  // ===================
  var Dropdown = function( element, option ) {
      
    // initialization element
    element = queryElement(element);
  
    // set option
    this.persist = option === true || element[getAttribute]('data-persist') === 'true' || false;
  
    // constants, event targets, strings
    var self = this, isOpen = false,
      parent = element[parentNode],
      component = 'dropdown', open = 'open',
      relatedTarget = null,
      menu = queryElement('.dropdown-menu', parent),
      children = nodeListToArray( menu[getElementsByTagName]('*')),
  
      // handlers
      keyHandler = function(e) {
        if (isOpen && (e.which == 27 || e.keyCode == 27)) { relatedTarget = null; hide(); } // e.keyCode for IE8
      },
      clickHandler = function(e) {
        var eventTarget = e[target], hasData;
        hasData = ( eventTarget.nodeType !== 1 && (eventTarget[getAttribute](dataToggle) || eventTarget[parentNode][getAttribute](dataToggle)) );
        if ( eventTarget === element || eventTarget === parent || eventTarget[parentNode] === element ) {
          e.preventDefault(); // comment this line to stop preventing navigation when click target is a link 
          relatedTarget = element;
          self.toggle();
        } else if ( isOpen ) {
          if ( (eventTarget === menu || children && children[indexOf](eventTarget) > -1) && ( self.persist || hasData ) ) {
            return;
          } else { relatedTarget = null; hide(); }
        }
        (/\#$/.test(eventTarget.href) || eventTarget[parentNode] && /\#$/.test(eventTarget[parentNode].href)) && e.preventDefault(); // should be here to prevent jumps
      },
      // private methods
      show = function() {
        bootstrapCustomEvent.call(parent, showEvent, component, relatedTarget);
        addClass(parent,open);
        menu[setAttribute](ariaExpanded,true);
        bootstrapCustomEvent.call(parent, shownEvent, component, relatedTarget);
        on(document, keydownEvent, keyHandler);
        isOpen = true;
      },
      hide = function() {
        bootstrapCustomEvent.call(parent, hideEvent, component, relatedTarget);
        removeClass(parent,open);
        menu[setAttribute](ariaExpanded,false);
        bootstrapCustomEvent.call(parent, hiddenEvent, component, relatedTarget);
        off(document, keydownEvent, keyHandler);
        isOpen = false;
      };
  
    // public methods
    this.toggle = function() {
      if (hasClass(parent,open) && isOpen) { hide(); } 
      else { show(); }
    };
  
    // init
    if ( !(stringDropdown in element) ) { // prevent adding event handlers twice
      menu[setAttribute]('tabindex', '0'); // Fix onblur on Chrome | Safari
      on(document, clickEvent, clickHandler);
    }
    element[stringDropdown] = this;
  };
  
  // DROPDOWN DATA API
  // =================
  initializeDataAPI( stringDropdown, Dropdown, dataToggle );

  return {
    Button: Button,
    Dropdown: Dropdown
  };
}));
