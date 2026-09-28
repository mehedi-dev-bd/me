// Ensure DOM is fully loaded to prevent intersection observer binding issues
document.addEventListener('DOMContentLoaded', () => {
    // Fade-in animation logic using Intersection Observer
    const faders = document.querySelectorAll('.fade-in');
    const appearOptions = { threshold: 0.1, rootMargin: "0px 0px -20px 0px" };

    const appearOnScroll = new IntersectionObserver(function(entries, appearOnScroll) {
        entries.forEach(entry => {
            if (!entry.isIntersecting) return;
            entry.target.classList.add('visible');
        });
    }, appearOptions);

    // Initial trigger on page load
    faders.forEach(fader => appearOnScroll.observe(fader));
});

// Function to switch between Face View, Student Content, and Developer Content
function showContent(sectionId) {
    const splitFace = document.getElementById('split-face-section');
    const studentContent = document.getElementById('student-content');
    const developerContent = document.getElementById('developer-content');

    // Hide all sections first
    splitFace.classList.add('d-none');
    studentContent.classList.add('d-none');
    developerContent.classList.add('d-none');

    // Show the requested section
    if (sectionId === 'student') {
        studentContent.classList.remove('d-none');
        triggerFadeIn();
    } else if (sectionId === 'developer') {
        developerContent.classList.remove('d-none');
        triggerFadeIn();
    } else {
        // Main view (Face split)
        splitFace.classList.remove('d-none');
    }

    // Scroll back to the top of the page smoothly
    window.scrollTo({ top: 0, behavior: 'smooth' });
}

// Reset animations so they play again when switching tabs
function triggerFadeIn() {
    const faders = document.querySelectorAll('.fade-in');
    
    // Re-create the observer for triggered animations
    const appearOptions = { threshold: 0.1, rootMargin: "0px 0px -20px 0px" };
    const appearOnScroll = new IntersectionObserver(function(entries, appearOnScroll) {
        entries.forEach(entry => {
            if (!entry.isIntersecting) return;
            entry.target.classList.add('visible');
        });
    }, appearOptions);

    faders.forEach(fader => {
        fader.classList.remove('visible'); 
        appearOnScroll.observe(fader);
    });
}