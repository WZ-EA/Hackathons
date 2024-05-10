import { Routes } from '@angular/router';

import { DashboardComponent } from './dashboard/dashboard.component';
import { QuestionsComponent } from './questions/questions.component';
import { CategoriesComponent } from './categories/categories.component';

export const routes: Routes = [
    // define paths for dashboard students and subjects
    {
        path: '',
        component: DashboardComponent
    },
    {
        path: 'categories',
        component: CategoriesComponent
    },
    {
        path: 'questions/:category',
        component: QuestionsComponent
    }
];