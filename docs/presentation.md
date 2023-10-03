---
marp: true
size: 16:9
theme: focusrite
paginate: true
class: invert
---

<!--
_paginate: skip
_class: lead
-->

![bg](img/title.png)

<!--
- Welcome

- Today we're going to go into the basics of making an accessible JUCE app.

- If you're here today I'm going to assume you're either a beginner to JUCE, or maybe you're not a beginner but maybe new to parts of JUCE which deal with accessibility (titles, roles, keyboard focus, etc). Or you're knowledgeable about both JUCE and accessibility but you're interested in how developers from a company like Focusrite has approached making an accessible app. In any case, you're all welcome here and I hope you get something valuable out of this.

- My goal today is to share small, specific examples that you can take, build from, and consider when making a JUCE app. Because of this, we won't be able to cover everything, and there are also plenty of ways to achieve the same thing! I'm going to try and make it fairly practical.
-->

---
<!--
- We're going to build an accessible JUCE app together. We'll start with a basic JUCE app that has had no effort put into accessibility, we'll assess it, and then improve it. During this I'll share some tools and tip that we found useful while developing accessible software.

- We'll be focussing mainly on stock JUCE components and the traditional JUCEy C++ way of GUI app development, though I'll maybe chat about other options towards the end.

- If we have time, I'll show you a real-world app I've worked on which takes and extends the concepts we've looked into today.
  
- Some pointers:
  - Today I'm going to use the word "accessible" mainly to refer to screen reader accessibility, which will be the focus today, since there are relatively new parts to JUCE that deal with it (well, it's been a bit over 2 years now since Ed initially added accessibility support in JUCE 6.1)
  - Not meaning to lessen the importance of localisation, visual customisation options, text sizing, colours, etc.
  - I use macOS primarily, so it's gonna be a bit mac-centric today, however the concepts are portable and it works on Windows screen readers too.
-->

<!--
_paginate: skip
_footer: Repository URL: [github.com/FocusriteGroup/accessible-juce-app-adc-23](https://github.com/FocusriteGroup/accessible-juce-app-adc-23)
-->

# Get the repository (slides in `docs/`)
![bg 25%](img/repo-qr.gif)

---

# Agenda

1. Demo of an app with default JUCE component accessibility
2. Dev tips for testing accessibility
3. Improving the app's accessibility
4. *Tour of an accessible app - Focusrite Control 2*
5. *Q&A*

---

# About me

- Software Developer Focusrite, since 2019
  - Scarlett 3rd Gen
  - Vocaster
  - Scarlett 4th Gen 🆕
- Musician 🎹
  - Psych pop, rock, jazz, weird boops & digital mess 🌈
- Love accessible software!

---

<!--
_class: lead
_footer: `git checkout ':/Initial commit'`
-->

<!--
I've built a small demo app designed to be simple, yet representative of a somewhat audio-related app. It's just a bunch of faders, buttons and text. It does nothing, it produces no audio, but it's hopefully better than a bunch of out-of-context examples.

During the development of Vocaster and Scarlett control software we discovered a lot through trial and error, so I wanted to share some more contextual examples to make it easier for others to learn.
-->

# Demo

---

# Testing accessibility

<!--
Time for a quick detour to discuss tools for testing accessibiliy.

These inspection tools are great for quickly interrogating your application to find out what accessibility information it reports.

There's the Accessibility Inspector on macOS, and the conveniently named Accessibility Ins-ights on Windows.

They give you a lot of information (almost too much sometimes), and IMO are particularly useful for inspecting the hierarchy of your components.

Although they are very good debugging tools, I don't think they're the best way to verify the accessibility of your application, the best way is to use the app yourself (and have others use it).
-->

- OS-specific tools
  - macOS: Accessibility Inspector (Xcode Developer Tool)
    [developer.apple.com/xcode](https://developer.apple.com/xcode/)
  - Windows: Accessibility Insights
    [accessibilityinsights.io](https://accessibilityinsights.io/)

---

# Use a screen reader

<!--
_footer: Interesting read: WebAIM Screen Reader Survey [webaim.org/projects/screenreadersurvey9/](https://webaim.org/projects/screenreadersurvey9/)
-->

<!--
This is the best way to check things whilst you're developing your app. If you don't rely on a screen reader for your day-to-day computing, then of course, if you're developing a product then you should also gather and act on feedback from folks who may have more experience than you. That being said, you should learn the basics so that you can set your app in the right direction, while you are coding it.

These are the main ones. There are various surveys such as the WebAIM one which seek to quantify screen reader usage, but these are the main ones and people will expect to be able to use them. There are some quirks with how some of them interact with JUCE. I won't be able to go into that today, but they mostly work the same.
-->

...for a more representative experience.

- macOS - VoiceOver
- Windows
  - Narrator
  - JAWS
  - NVDA

---

# Streamline your experience

<!--
To me, developing accessible software means embracing the accessibility tools.

In order to ensure the accessibility of your app/plugin, make testing it part of your workflow if it isn't already.

Shortcuts to turn VoiceOver on - Cmd+F5.

Enable the Accessibility Shortcuts in the menu bar.

Turn up the speed of the speech, the default is a bit slow for me.

You can also toggle muting the speech in VoiceOver utility (to _temporarily_ use the caption panel instead, whilst leaving the screen reader running). You can set up a keyboard shortcut to do this.

I learnt this is very useful when coding with colleagues on a video call (i.e. in a post-pandemic world). When debugging a UI issue, we're often wanting to leave VoiceOver on, to show the focus ring and caption panel, whilst talking amongst ourselves without VoiceOver getting in the way.
-->

- Do a tutorial (decent one often built-in to the screenreader)
- Learn the shortcuts, e.g. on macOS:
  - `cmd + F5` to toggle VoiceOver
  - VO key: `caps lock` or `ctrl + alt`
- Turn up the speed (if you wish)
- Know how to silence it (`ctrl` on mac)
- Set up toggle speech mute (_temporarily_ use the caption panel instead)

---

<!--
To set up a speech muting toggle, go to VoiceOver utility and add a keyboard shortcut under the "Commanders" tab, for "Mute speech toggle". This can then be activated using the option key and the key that you have assigned, I use "z".

It will still give you lovely audio feedback when moving over components (clicky sounds which pan depending on where the component is on screen).
-->

# Toggling speech mute

![bg 80% Screenshot of VoiceOver utility](img/vo-utility.png)

---

<!--
_class: lead
-->

# Back to the demo

---

# Issues 😕

❌ Can't interact with the keyboard alone

❌ Titles missing

❌ Unclear grouping ("mute" for what?)

❌ Not clear that buttons can be toggled

❌ (Windows) Expected the space bar would trigger buttons

❌ Sliders not receiving keyboard focus

❌ Strange focus order

---

<!--
_class: lead
_footer: `git checkout ':/Fix application window'`
-->

<!--
So, let's fix the initial keyboard interaction
-->

# Fixing the initial keyboard interaction

---

# The (counterintuitive) fix

<!--
To me this seems counterintuitive.

This is all because in the constructor of TopLevelWindow, it calls setWantsKeyboardFocus(true)

However, we had to do this fix in all our apps and I notice the Projucer does this as well so.
-->

- Call `setWantsKeyboardFocus (false)` on the `DocumentWindow`
  - Otherwise keyboard focus becomes trapped on the window component
- Alternatively, inherit `activeWindowStatusChanged` and grab keyboard focus of the main content component when visible

---

# Issues

✅ Can't interact with the keyboard alone - fixed!

❌ Titles missing

❌ Unclear grouping ("mute" for what?)

❌ Not clear that buttons can be toggled

❌ (Windows) Expected the space bar would trigger buttons

❌ Sliders not receiving keyboard focus

❌ Strange focus order

---

<!--
_class: lead
_footer: `git checkout ':/Add titles'`
-->

# Adding titles

---

# Issues

✅ Can't interact with the keyboard alone - fixed!

✅ Titles missing - fixed!

❌ Unclear grouping ("mute" for what?)

❌ Not clear that buttons can be toggled

❌ (Windows) Expected the space bar would trigger buttons

❌ Sliders not receiving keyboard focus

❌ Strange focus order

---
<!--
_class: lead
_footer: `git checkout ':/Make channel strip a focus container'`
-->

# Fixing the grouping

---

<!--
Empty groups now we've added the titles?

In JUCE, there are 2 kinds of focus container: regular, and keyboard.

Focus container: "The component will act as a top-level component within which focus is passed around."

Keyboard focus container: "The component will act as a top-level component within which keyboard focus is passed around."

Given those descriptions, it can be hard to make the distinction between the two. The difference all comes down to what happens when you press tab to move the focus.

The regular focus container is essentially a tool to indicate component grouping to the OS, and in turn, the screen reader. The component will be announced as a "group", and on VoiceOver for example, you'll be able to navigate in and out of the group with VO+Shift+Down and VO+Shift+Up. If you keep doing VO+Right, you'll eventually hit the end of the group, and depending on your VoiceOver settings, it'll trap the screen reader focus inside the group. To exit the group, you can do VO+Shift+Up.

With the keyboard focus container,
-->

# Focus containers

- Components have the "group" role by default
- You have to specify the focus behaviour
  - `juce::Component::FocusContainerType::focusContainer`
  - `juce::Component::FocusContainerType::keyboardFocusContainer`

---

<!--
Side note - *slight* difference with interaction of a component hierarchy, between operating systems
-->

# Side note: design considerations

- Windows screen readers generally keyboard focus-oriented (i.e. using tab to move around)
- Tab used for macOS/VoiceOver as well, but also VO + arrow keys, for traversing the layout

---

# Issues

✅ Can't interact with the keyboard alone - fixed!

✅ Titles missing - fixed!

✅ Unclear grouping - fixed!

❌ Not clear that buttons can be toggled

❌ (Windows) Expected the space bar would trigger buttons

❌ Sliders not receiving keyboard focus

❌ Strange focus order

---

<!--
_class: lead
_footer: `git checkout ':/Support toggle button role'`
-->

# Fixing the buttons

---

# Accessibility Handlers
<!--
The problem here is because we're using juce::TextButton. The stock JUCE TextButton always announces as just being a "button", maybe TextButtons were just designed for single fire actions, but hey, we want it to toggle! Sure, you could use a juce::ToggleButton but that's more designed to be for checkboxes and sliding toggles, like the ones you'd find in the preferences. We could refactor our button to make it a juce::ToggleButton but then we'd have to go down the route of rewriting the text drawing and layout that the TextButton does so nicely for us... what if we don't want to do that right now?

Well, we need our button to announce as having a togglebutton accessibility role. To do this, we need to override `createAccessibilityHandler` and return an accessibility handler which contains the correct role.

Actions: how the component allows being interacted with (e.g. press, toggle, show context menu)
Interface: how the component's value is set and retrieved by the client
-->

- Write a custom accessibility handler from scratch

```C++
juce::AccessibilityHandler (juce::Component& componentToWrap,
                            juce::AccessibilityRole accessibilityRole, // yaaas
                            juce::AccessibilityActions actions = {},
                            juce::Interfaces interfaces = {});
```

- Override `createAccessibilityHandler` in our custom button class:

```C++
std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler () override;
```

- JUCE's Button accessibility handler is about 120 lines long...
  - We'd end up duplicating that


---

# No need to reinvent the wheel
<!--
The JUCE button accessibility handler can be accessed through the `detail` namespace. Not perfect practice, but this pragmatic solution will get us going!

-->
- In the cpp file of your custom button class...

```C++
#include <juce_gui_basics/detail/juce_ButtonAccessibilityHandler.h>

std::unique_ptr<juce::AccessibilityHandler> Button::createAccessibilityHandler () {
    return std::make_unique<juce::detail::ButtonAccessibilityHandler> (*this,
                                                                       isToggleable ()
                                                                           ? juce::AccessibilityRole::toggleButton
                                                                           : juce::AccessibilityRole::button);
}
```
- ⚠️ This is using JUCE implementation detail and could change
  - Given it's a very specific class, maybe that's what we want
- ⚠️ It could be removed in the future
  - Then we can just write our accessibility handler from scratch
---

# Issues

✅ Can't interact with the keyboard alone - fixed!

✅ Titles missing - fixed!

✅ Unclear grouping - fixed!

✅ Not clear that buttons can be toggled - fixed!

❌ (Windows) Expected the space bar would trigger buttons

❌ Strange focus order

❌ Where are the sliders?

---
<!--
_class: lead
_footer: `git checkout ':/Allow space bar'`
-->

# Making space bar trigger buttons

---

# Making space bar trigger buttons

- `juce::Button::addShortcut` doesn't do what you think!
- Instead, override `keyPressed` and make it trigger on `return` and `space`

```C++
bool keyPressed (const juce::KeyPress & key) override {
    if (! isEnabled ())
        return false;

    if (key == juce::KeyPress::returnKey || key == juce::KeyPress::spaceKey) {
        triggerClick ();
        return true;
    }

    return false;
}
```

---

# Issues

✅ Can't interact with the keyboard alone - fixed!

✅ Titles missing - fixed!

✅ Unclear grouping - fixed!

✅ Not clear that buttons can be toggled - fixed!

✅ (Windows) Expected the space bar would trigger buttons - fixed!

❌ Sliders not receiving keyboard focus

❌ Strange focus order

---

<!--
_class: lead
_footer: `git checkout ':/Allow sliders'`
-->

# Letting the sliders receive keyboard focus

---

# Issues

✅ Can't interact with the keyboard alone - fixed!

✅ Titles missing - fixed!

✅ Unclear grouping - fixed!

✅ Not clear that buttons can be toggled - fixed!

✅ (Windows) Expected the space bar would trigger buttons - fixed!

✅ Sliders not receiving keyboard focus - fixed!

❌ Strange focus order

---

<!--
_class: lead
_footer: `git checkout ':/Set explicit focus order'`
-->

# Fixing the focus order

---

# Focus orders

## Focus traverser

- Default JUCE keyboard focus traverser goes top-to-bottom, _then_ left to right
- You may run into issues depending on how you draw your component within its bounds.

---

<!--
So for the first example we have 2 rectangles side by side, the left-hand one is horizontal (on it's side), the right-hand one is one vertical (standing up).

Since the default JUCE keyboard focus traverser priorities top-down, in this space, the right hand one has a higher vertical position.

Visually, that doesn't feel correct to me (with my bias of western writing systems), given they exist in the same row, it should still go left to right.

(Side note: would be useful if `FlexBox`/`Grid` overrode this, and went via main axis/cross axis)

-->

## Figure 1: Right-hand component goes first

![bg 50% Diagram of 2 rectangles sitting side by side. The first one is horizontal, the second one is vertical, meaning the second one has a higher top position.](img/focus-group-2.svg)

---

<!--
For the second example we have the same 2 side-by-side rectangles (one horizontal, one vertical), however each is drawn within it's own square container. The squares are now the top level components.

Since the vertical/Y positions of the squares are the same, the default traverser then looks left to right, so the left-hand component now goes first.

Something to keep in mind!

-->

## Figure 2: Left-hand component goes first

![bg 50% Diagram of 2 rectangles sitting side by side. This time they are both drawn within square containers, meaning they share the same top position.](img/focus-group-1.svg)

---

<!--
So there are a number of ways to customise the focus order. You can manually set the order, you can create your own focus traverser algorithm from scratch, or something which I've found quite useful which we'll have a look at now.

I'm not going to go into the custom focus traverser stuff today because I've actually never had to use it. It requires fiddling around with Component pointers and keeping track of arrays of components, I've never had a complex enough of a scenario to warrant needing one - i.e. massively dynamic layout.
-->

# Focus order solutions

- Manually set explicit focus order
- Custom `juce::KeyboardFocusTraverser`
  - Possibly overkill for static layouts

or

- Semi-automatically set explicit focus order

<!--_footer: 'Reference: [docs.juce.com/master/classComponentTraverser.html](https://docs.juce.com/master/classComponent.html)'-->

---

# Basic fix

```C++
SomeContainerComponent() {
    someButton.setExplicitFocusOrder (1); // Starts from 1
    somePanSlider.setExplicitFocusOrder (2);
    someLevelSlider.setExplicitFocusOrder (3);
}
```

---

<!--
You can create an order that starts with a specified component, continuing with other specified components using the "then" method, building up an order. You can use this whenever the order changes.
-->

# A neat little focus order utility

```C++
SomeContainerComponent() {
    ExplicitFocusOrder::startingWith (someButton)
        .then (somePanSlider)
        .then (someLevelSlider);
}
```

---

<!--
Here's the implementation, omitting constructor/destructor business (rule of 3 / rule of 5 / rule of 42...) for the purpose of slideware.
-->

## Behind the scenes

```C++
class ExplicitFocusOrder {
public:
    static ExplicitFocusOrder startingWith (juce::Component & component) {
        return ExplicitFocusOrder {}.then (component);
    }

    ExplicitFocusOrder & then (juce::Component & component) {
        component.setExplicitFocusOrder (m_index);
        index += 1;
        return *this;
    }
private:
    int index {1};
};
```

---

# Issues

✅ Can't interact with the keyboard alone - fixed!

✅ Titles missing - fixed!

✅ Unclear grouping - fixed!

✅ Not clear that buttons can be toggled - fixed!

✅ (Windows) Expected the space bar would trigger buttons - fixed!

✅ Sliders not receiving keyboard focus - fixed!

✅ Strange focus order - fixed!

---

<!--
_class: lead
-->

# We did it! 🎏

---

# Further reading & thoughts

<!--
More info on how JUCE accessibility works, how it interacts with the different accessibility APIs

Web views

I'd recommend Sudara's "Melatonin Inspector" JUCE module. It attaches an inspector-style window to your JUCE app that shows a whole host of information, including keyboard focus and component hierarchies. Not dissimilar to something like accessibility inspector, but in the context of JUCE components (and does a whole lot more visual stuff too)

-->

- Ed Davies - *Making JUCE Accessible*
  [youtu.be/BqrEv4ApH3U](https://www.youtube.com/watch?v=BqrEv4ApH3U)

- Web views are gaining popularity - *perhaps* consider it
  - Cross-platform accessibility naturally better, due to way content is declaritively "marked up"
  - Tricky decision!
- Sudara's Melatonin Inspector JUCE module
[github.com/sudara/melatonin_inspector](https://github.com/sudara/melatonin_inspector)

---

# Quick tour of Focusrite Control 2

<!--
Now I thought it'd be a good idea to show you a fully-fledged example of an accessible JUCE app, and a project that I've worked on with a wonderful group of people over the last year or so.

The software in question is Focsurite Control 2, which is the control software for our 4th generation Scarlett interfaces. It's built using JUCE and runs on macOS and Windows. As well as it being screen reader accessible, it's got an auto-updater (which bundles firmware updates too), has localisation support, opt-in analytics and a streamlined user interface designed to help set your Scarlett interface up easily. It may not sound it, but trust me, it's exciting.

It also happens to be quite a nice app for demonstrating accessibility, because it has a simple structure and is comprised of simple components (sliders/buttons/etc)
-->

![bg 45% Screenshot of Focusrite Control 2](img/fc2-mixer.png)

---

<!--_class: lead-->

<!--
As an aside, if you're interested in learning more about how our hardware interacts with our software, check out Joe Noël's talk from ADC 2020.
-->

# More info about our software stack(s)

Joe Noël - _Stack Overflow: A Tour of the Software Stack at Focusrite_

[youtu.be/Xe2r9_CqqkY](https://youtu.be/Xe2r9_CqqkY)

---

<!--_class: lead-->

# More accessibility...

Cain McCormack - _Launchpad iOS: An Accessibility Journey_ [youtu.be/ShJun3X1BE4](https://youtu.be/ShJun3X1BE4)

---

<!--
Thanks for your time, I hope you've learnt something, even if its just some perspectives! Through sharing bits and pieces I hope that we can all help make this industry more accessible to all.

-->
<!--
_paginate: skip
_class: lead
footer:
-->

# Thanks for listening 👋

📧 harry.morley@focusrite.com

🏛️ `hmorley` @ JUCE Forum

🏛️ ADC 2023 Discord

🕸️ [harrymorley.net](https://harrymorley.net)

---

<!--
_paginate: skip
_class: lead
-->

P.S. We're hiring
[apply.workable.com/focusrite](https://apply.workable.com/focusrite)

---

<!--
_paginate: skip
_class: lead
-->

P.P.S. Shout-out to James J for the help with the look-and-feel 🙏

And to the rest of the Scarlett team for the support 🙌

---
<!--
_paginate: skip
-->

---
<!--
_paginate: skip
_class: lead
-->

# Addendum

---
<!--_footer: 'Reference: [docs.juce.com/master/classComponent.html](https://docs.juce.com/master/classComponent.html)'-->
# Accessibility toolkit: basics

<!--
Here are the functions that you will find yourself coming back to. If you're experienced, these will be old news to you, but it's good to keep these at the top of your mind.

Description, further info about the component.

On mac with VoiceOver, help text can read with VO+Shift+H. Can be useful for working around slightly awkward interactions, e.g. "press to reset indicator".
-->

- `juce::Component::setAccessible (...)`
- `juce::Component::setTitle (...)`
- `juce::Component::setFocusContainerType (...)`
- `juce::Component::setDescription (...)`
- `juce::Component::setHelpText (...)`

---

<!--_footer: 'Reference: [docs.juce.com/master/classComponent.html](https://docs.juce.com/master/classComponent.html)'-->

# Accessibility toolkit: advanced

<!--
Here are some others which we saw today. Maybe not as common but you'll likely run into these at some point.
-->

- `juce::Component::setExplicitFocusOrder (...)`
- `juce::KeyboardFocusTraverser`
- `juce::Component::createAccessibilityHandler ()`
